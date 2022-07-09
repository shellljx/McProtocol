//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "Packet.h"

namespace McProtocol {
enum class ProtocolStatus { NONE, HANDSHAKE ,STATUS, LOGIN, PLAY };
class PacketFactory {
 public:
  explicit PacketFactory();
  ~PacketFactory();

  std::unique_ptr<Packet> createServerBoundPacket(int id);
  std::unique_ptr<Packet> createClientBoundPacket(int id);

  void setProtocolStatus(ProtocolStatus status) {
    status_ = status;
  }

  ProtocolStatus getProtocolStatus() {
    return status_;
  }

 private:
  ProtocolStatus status_ = ProtocolStatus::NONE;
};
}
