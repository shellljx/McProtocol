//
// Created by 李金祥 on 2022/5/28.
//

#include "StatusResponsePacket.h"

namespace McProtocol {
StatusResponsePacket::StatusResponsePacket() : Packet(0) {
}

StatusResponsePacket::~StatusResponsePacket() noexcept {
}

void StatusResponsePacket::write(EncodeStream *stream) {

}

void StatusResponsePacket::read(DecodeStream *stream) {

}
}