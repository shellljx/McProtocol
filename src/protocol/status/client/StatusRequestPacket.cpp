//
// Created by 李金祥 on 2022/5/28.
//

#include "StatusRequestPacket.h"

namespace McProtocol {
StatusRequestPacket::StatusRequestPacket() : Packet(0) {
}

StatusRequestPacket::~StatusRequestPacket() = default;

void StatusRequestPacket::write(EncodeStream *stream) {

}

void StatusRequestPacket::read(DecodeStream *stream) {

}
}