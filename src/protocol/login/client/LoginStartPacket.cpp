//
// Created by 李金祥 on 2022/5/29.
//

#include "LoginStartPacket.h"
namespace McProtocol {
LoginStartPacket::LoginStartPacket() : Packet(0x00) {
}

LoginStartPacket::~LoginStartPacket() noexcept {
}

void LoginStartPacket::write(EncodeStream *stream) {
  stream->writeUTF8String(userName);
}

void LoginStartPacket::read(DecodeStream *stream) {
  userName = stream->readUTF8String();
}
}