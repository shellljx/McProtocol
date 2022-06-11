//
// Created by 李金祥 on 2022/5/31.
//

#include "ClientStatusPacket.h"

namespace McProtocol {
ClientStatusPacket::ClientStatusPacket() : Packet(0x04) {
}

ClientStatusPacket::~ClientStatusPacket() = default;

void ClientStatusPacket::write(EncodeStream *stream) {
  stream->writeVarInt(action_);
}

void ClientStatusPacket::read(DecodeStream *stream) {
  action_ = stream->readVarInt();
}
}