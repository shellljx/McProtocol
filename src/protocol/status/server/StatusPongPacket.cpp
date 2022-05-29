//
// Created by 李金祥 on 2022/5/29.
//

#include "StatusPongPacket.h"

namespace McProtocol {
StatusPongPacket::StatusPongPacket() : Packet(0x01) {
}

StatusPongPacket::~StatusPongPacket() noexcept {
}

void StatusPongPacket::write(EncodeStream *stream) {
  stream->writeInt64(pingTime);
}

void StatusPongPacket::read(DecodeStream *stream) {
  pingTime = stream->readInt64();
}
}