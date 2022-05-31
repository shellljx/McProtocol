#include <iostream>
#include <thread>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <zlib.h>

#include "src/io/ByteData.h"
#include "src/io/EncodeStream.h"
#include "src/io/DecodeStream.h"
#include "src/protocol/Packet.h"
#include "src/protocol/handshake/HandshakePacket.h"
#include "src/protocol/status/client/StatusRequestPacket.h"
#include "src/protocol/status/server/StatusResponsePacket.h"
#include "src/protocol/status/client/StatusPingPacket.h"
#include "src/protocol/status/server/StatusPongPacket.h"
#include "src/protocol/login/server/LoginSuccess.h"
#include "src/protocol/login/server/SetCompressionPacket.h"
#include "src/protocol/ingame/client/ClientKeepAlivePacket.h"
#include "src/protocol/ingame/server/ServerKeepAlivePacket.h"
#include "src/codec/EncryptionCodec.h"
#include "src/codec/SizerCodec.h"
#include "src/codec/CompressionCodec.h"
#include "src/protocol/PacketFactory.h"

int client_socket;

std::queue<std::unique_ptr<McProtocol::Packet>> packets_to_send;
std::mutex mutex_send;
std::condition_variable send_condition;

std::queue<std::unique_ptr<McProtocol::Packet>> packets_to_process;
std::mutex mutex_process;
std::condition_variable process_condition;

bool enableEncryption = false;
McProtocol::EncryptionCodec encryptionCodec;
McProtocol::SizerCodec sizerCodec;
McProtocol::CompressionCodec compressionCodec;
bool enableCompression = false;
int compressionThreshold;

McProtocol::PacketFactory packetFactory;

void sendPacket(std::unique_ptr<McProtocol::Packet> packet) {
  if (packet == nullptr) {
    return;
  }
  std::unique_lock<std::mutex> lock(mutex_send);
  packets_to_send.push(std::move(packet));
  send_condition.notify_all();
}
bool a = true;
void createClientBoundPacket(McProtocol::DecodeStream *stream) {
  int packetid = stream->readVarInt();
  std::cout<<"packet: "<<packetid<<std::endl;
  auto packet = packetFactory.createClientBoundPacket(packetid);
  if (packet == nullptr) {
    return;
  }
  packet->read(stream);

  if (packetFactory.getProtocolStatus() == McProtocol::ProtocolStatus::LOGIN) {
    if (packetid == 3){
      auto p = reinterpret_cast<McProtocol::SetCompressionPacket *>(packet.get());
      enableCompression = true;
      compressionCodec.setEnable(true);
      compressionThreshold = p->getCompressionThreshold();
    } else if (packetid == 2){
      packetFactory.setProtocolStatus(McProtocol::ProtocolStatus::INGAME);
    }
  }

  if (packetFactory.getProtocolStatus() == McProtocol::ProtocolStatus::INGAME) {
    auto livep = reinterpret_cast<McProtocol::ServerKeepAlivePacket*>(packet.get());
    if (packetid == 0x21){
      auto op = std::unique_ptr<McProtocol::ClientKeepAlivePacket>(new McProtocol::ClientKeepAlivePacket);
      op->setKeepAliveId(livep->getKeepAliveId());
      sendPacket(std::move(op));
      if (a){
        sendPacket(packetFactory.createServerBoundPacket(0x04));
        a = false;
      }
    }
  }

  std::unique_lock<std::mutex> lock(mutex_process);
  packets_to_process.push(std::move(packet));
  process_condition.notify_all();
}

void ReadThread() {
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(25565);
  auto ret = connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (ret != 0) {
    throw std::runtime_error("connect error");
  }
  printf("connected %d", ret);

  packetFactory.setProtocolStatus(McProtocol::ProtocolStatus::HANDSHAKE);
  sendPacket(packetFactory.createServerBoundPacket(0x00));
  packetFactory.setProtocolStatus(McProtocol::ProtocolStatus::LOGIN);
  sendPacket(packetFactory.createServerBoundPacket(0x00));

  McProtocol::EncodeStream encodeStream(256);
  while (true) {
    unsigned char buffer[256];
    int length = read(client_socket, buffer, sizeof(buffer));
    //std::cout << "receive " << length << std::endl;
    if (length == 0) {
      close(client_socket);
      return;
    }

    //encrypttion codec
    {
      auto byteData = encryptionCodec.decode(buffer, length);
      encodeStream.writeBytes(byteData->data(), byteData->length());
    }

    //sizer codec
    auto byteData = encodeStream.release();
    McProtocol::DecodeStream decode_stream(byteData->data(), byteData->length());
    while (decode_stream.bytesAvailable() > 0) {
      auto packetDecodeStream = sizerCodec.decode(decode_stream);
      if (packetDecodeStream.data() == nullptr) {
        break;
      }
      //compression codec
      auto packetByteData = compressionCodec.decode(packetDecodeStream);
      McProtocol::DecodeStream decode_stream1(packetByteData->data(), packetByteData->length());
      createClientBoundPacket(&decode_stream1);
    }

    if (decode_stream.bytesAvailable() > 0) {
      encodeStream.writeBytes(decode_stream.data(), decode_stream.bytesAvailable(), decode_stream.position());
    }
    if (encodeStream.length() == 100000) {
      break;
    }
  }
}

std::unique_ptr<McProtocol::ByteData> compression(McProtocol::DecodeStream *in) {
  int ret;
  int chunk = 1024 * 6;
  unsigned have;
  z_stream strm;
  memset(&strm, 0, sizeof(strm));
  ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
  if (ret != Z_OK) {
    throw std::runtime_error("deflate init error");
  }
  unsigned char input[in->bytesAvailable()];
  memcpy(input, in->data(), in->bytesAvailable());
  unsigned char output[chunk];
  McProtocol::EncodeStream outStream;

  strm.avail_in = in->bytesAvailable();
  strm.next_in = input;
  do {
    strm.avail_out = chunk;
    strm.next_out = output;
    ret = deflate(&strm, Z_FINISH);
    assert(ret != Z_STREAM_ERROR);
    have = chunk - strm.avail_out;
    outStream.writeBytes(output, have);
  } while (strm.avail_out == 0);
  deflateEnd(&strm);
  return outStream.release();
}

void SendThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex_send);
    while (packets_to_send.empty()) {
      send_condition.wait(lock);
    }
    auto packet = std::move(packets_to_send.front());
    packets_to_send.pop();
    lock.unlock();

    McProtocol::EncodeStream stream;
    //write packet and length
    stream.writeVarInt(packet->getPacketId());
    packet->write(&stream);
    auto byteData = stream.release();

    //compression
    if (enableCompression) {
      if (byteData->length() < compressionThreshold) {
        stream.writeVarInt(0);
        stream.writeByteData(byteData.get());
      } else {
        stream.writeVarInt(byteData->length());
        McProtocol::DecodeStream stream1(byteData->data(), byteData->length());
        auto compressByteDat = compression(&stream1);
        stream.writeByteData(compressByteDat.get());
      }
      byteData = stream.release();
    }

    //sizer
    stream.writeVarInt(byteData->length());
    stream.writeByteData(byteData.get());
    byteData = stream.release();

    //encryption
    if (enableEncryption) {
      unsigned char *out = nullptr;
      int outLength = 0;
      encryptionCodec.encode(byteData->data(), byteData->length(), out, outLength);
      byteData = McProtocol::ByteData::MakeCopy(out, outLength);
    }

    write(client_socket, byteData->data(), byteData->length());
    std::cout << "packet send" << std::endl;
    if (packets_to_send.size() == 100000) {
      break;
    }
  }
}

void PackageThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex_process);
    while (packets_to_process.empty()) {
      process_condition.wait(lock);
    }
    auto packet = std::move(packets_to_process.front());
    packets_to_process.pop();
    lock.unlock();
    //process
    if (packetFactory.getProtocolStatus() == McProtocol::ProtocolStatus::STATUS) {
      if (packet->getPacketId() == 0x00) {
        auto p = reinterpret_cast<McProtocol::StatusResponsePacket *>(packet.get());
        std::cout << p->getInfo() << std::endl;
        auto ping = packetFactory.createServerBoundPacket(0x01);
        reinterpret_cast<McProtocol::StatusPingPacket *>(ping.get())->setPayload(12345678910);
        sendPacket(std::move(ping));
      }
      if (packet->getPacketId() == 0x01) {
        auto p = reinterpret_cast<McProtocol::StatusPongPacket *>(packet.get());
        std::cout << p->getPayload() << std::endl;
      }
    } else if (packetFactory.getProtocolStatus() == McProtocol::ProtocolStatus::LOGIN) {
      if (packet->getPacketId() == 0x02) {
        auto p = reinterpret_cast<McProtocol::LoginSuccessPacket *>(packet.get());
        std::cout << "name: " << p->getUserName() << " UUID: " << p->getUUID() << std::endl;
      }
    }

    if (packets_to_process.size() == 100000) {
      break;
    }
  }
}

int main() {

  std::cout << "start" << std::endl;
  std::thread thread_read = std::thread(&ReadThread);
  std::thread thread_write = std::thread(&SendThread);
  std::thread thread_package = std::thread(&PackageThread);

  if (thread_read.joinable()) {
    thread_read.join();
  }

  if (thread_write.joinable()) {
    thread_write.join();
  }

  if (thread_package.joinable()) {
    thread_package.join();
  }
  //============

  return 0;
}
