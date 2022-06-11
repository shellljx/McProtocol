//
// Created by 李金祥 on 2022/5/28.
//

#include "HandshakePacket.h"

namespace McProtocol {
HandshakePacket::HandshakePacket() : Packet(0) {

}

HandshakePacket::~HandshakePacket() = default;

void HandshakePacket::write(EncodeStream *stream) {
  stream->writeVarInt(protocolVersion_);
  stream->writeVarString(serverAddr_);
  stream->writeInt16(serverPort);
  stream->writeVarInt(intent);
}

void HandshakePacket::read(DecodeStream *stream) {

}
}