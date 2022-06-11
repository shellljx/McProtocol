//
// Created by 李金祥 on 2022/5/29.
//

#include "LoginSuccess.h"

namespace McProtocol {
LoginSuccessPacket::LoginSuccessPacket() : Packet(0x02) {
}

LoginSuccessPacket::~LoginSuccessPacket() = default;

void LoginSuccessPacket::write(EncodeStream *stream) {

}

void LoginSuccessPacket::read(DecodeStream *stream) {
  int64_t u1 = stream->readInt64();
  int64_t u2 = stream->readInt64();
  uuid = std::to_string(u1) + std::to_string(u2);
  userName = stream->readVarString();
}
}