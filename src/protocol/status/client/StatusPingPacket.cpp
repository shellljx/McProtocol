//
// Created by 李金祥 on 2022/5/29.
//

#include "StatusPingPacket.h"

namespace McProtocol {
StatusPingPacket::StatusPingPacket() : Packet(0x01) {
}

StatusPingPacket::~StatusPingPacket() noexcept {
}

void StatusPingPacket::write(EncodeStream *stream) {
  stream->writeInt64(pingTime);
}

void StatusPingPacket::read(DecodeStream *stream) {
  pingTime = stream->readInt64();
}
}