//
// Created by 李金祥 on 2022/5/31.
//

#include "ServerKeepAlivePacket.h"

namespace McProtocol {
ServerKeepAlivePacket::ServerKeepAlivePacket() : Packet(0x21) {
}

ServerKeepAlivePacket::~ServerKeepAlivePacket() noexcept {
}

void ServerKeepAlivePacket::write(EncodeStream *stream) {

}

void ServerKeepAlivePacket::read(DecodeStream *stream) {
  keepAliveId_ = stream->readInt64();
}
}