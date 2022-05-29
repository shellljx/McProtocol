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
#include "src/codec/EncryptionCodec.h"

int client_socket;

std::queue<McProtocol::Packet *> packets_to_send;
std::mutex mutex_send;
std::condition_variable send_condition;

bool enableEncryption = false;
McProtocol::EncryptionCodec encryptionCodec;
bool enableCompression = false;

static void resize() {

}

void processPacket(McProtocol::Packet *packet) {

}

static void onConnected() {
  std::unique_lock<std::mutex> lock(mutex_send);
  packets_to_send.push(new McProtocol::HandshakePacket());
  packets_to_send.push(new McProtocol::StatusRequestPacket());
  send_condition.notify_all();
}

std::unique_ptr<McProtocol::ByteData> decomp(McProtocol::DecodeStream *stream) {
  auto dataLength = stream->readVerInt();

  int ret;
  int chunk = 1024 * 6;
  unsigned have;
  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;

  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    throw std::runtime_error("zlib init failed");
  }
  unsigned char input[stream->bytesAvailable()];
  uint32_t avaliable = stream->bytesAvailable();
  memcpy(input, stream->readBytes(avaliable).data(), avaliable);
  strm.avail_in = stream->bytesAvailable();
  strm.next_in = input;
  unsigned char output[chunk];
  McProtocol::EncodeStream outStream(dataLength);
  do {
    strm.avail_out = chunk;
    strm.next_out = output;
    ret = inflate(&strm, Z_NO_FLUSH);
    assert(ret != Z_STREAM_ERROR);
    switch (ret) {
      case Z_NEED_DICT:ret = Z_DATA_ERROR;
      case Z_DATA_ERROR:
      case Z_MEM_ERROR: {
        inflateEnd(&strm);
        throw std::runtime_error("zlib inflate error");
      }
    }
    have = chunk - strm.avail_out;
    outStream.writeBytes(output, have);
  } while (strm.avail_out == 0);
  inflateEnd(&strm);
  return outStream.release();
}

McProtocol::Packet *createPacket(const McProtocol::DecodeStream *stream) {
  return new McProtocol::StatusResponsePacket();
}

void ReadThread() {
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(25565);
  auto ret = connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
  printf("connected %d", ret);
  onConnected();

  McProtocol::EncodeStream encodeStream(256);
  while (true) {
    auto buffer = new unsigned char[256];
    int length = read(client_socket, buffer, sizeof(buffer));
    std::cout << "receive" << length << std::endl;
    if (length == 0) {
       close(client_socket);
      return;
    }

    if (enableEncryption) {
      unsigned char *out = nullptr;
      int outLength = 0;
      encryptionCodec.decode(buffer, length, out, outLength);
      delete[] buffer;
      encodeStream.writeBytes(out, outLength);
    } else {
      encodeStream.writeBytes(buffer, length);
    }

    auto byteData = encodeStream.release();

    McProtocol::DecodeStream decode_stream(byteData->data(), byteData->length());
    while (decode_stream.bytesAvailable() > 0) {
      auto packetLength = decode_stream.readVerInt();
      if (packetLength > 0 && packetLength <= decode_stream.bytesAvailable()) {
        auto packetStream = decode_stream.readBytes(packetLength);

        int packetid = packetStream.readVerInt();
        std::string info = packetStream.readUTF8String();
        printf("");
        //auto packet = createPacket(&packetStream);
        //packet->read(&packetStream);
        //processPacket(packet);
      } else {
        decode_stream.setPosition(0);
        break;
      }
    }

    if (decode_stream.bytesAvailable() > 0) {
      encodeStream.writeBytes(decode_stream.data(), decode_stream.bytesAvailable(), decode_stream.position());
    }
    if (encodeStream.length() == 100000) {
      break;
    }
  }
}

void SendThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex_send);
    while (packets_to_send.empty()) {
      send_condition.wait(lock);
    }
    auto packet = packets_to_send.front();
    packets_to_send.pop();

    McProtocol::EncodeStream stream;
    stream.writeVarInt(packet->getPacketId());
    packet->write(&stream);
    auto byteData = stream.release();
    stream.writeVarInt(byteData->length());
    stream.writeByteData(byteData.get());
    auto byte2 = stream.release();
    write(client_socket, byte2->data(), byte2->length());
    std::cout << "packet send" << std::endl;
  }
}

void PackageThread() {

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
