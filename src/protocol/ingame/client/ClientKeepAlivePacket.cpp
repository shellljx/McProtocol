//
// Created by 李金祥 on 2022/5/31.
//

#include "ClientKeepAlivePacket.h"

namespace McProtocol {
ClientKeepAlivePacket::ClientKeepAlivePacket() : Packet(0x0F) {
}

ClientKeepAlivePacket::~ClientKeepAlivePacket() noexcept {
}

void ClientKeepAlivePacket::write(EncodeStream *stream) {
  stream->writeInt64(keepAliveId_);
}

void ClientKeepAlivePacket::read(DecodeStream *stream) {
}
}