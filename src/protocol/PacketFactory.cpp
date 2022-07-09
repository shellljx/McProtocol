//
// Created by 李金祥 on 2022/5/29.
//

#include "PacketFactory.h"
#include "./handshake/HandshakePacket.h"
#include "./status/client/StatusRequestPacket.h"
#include "./status/server/StatusResponsePacket.h"
#include "./status/client/StatusPingPacket.h"
#include "./status/server/StatusPongPacket.h"
#include "./login/client/LoginStartPacket.h"
#include "./login/server/LoginSuccess.h"
#include "./login/server/SetCompressionPacket.h"
#include "ingame/clientbound/ServerKeepAlivePacket.h"
#include "ingame/serverbound/ClientKeepAlivePacket.h"
#include "ingame/serverbound/ClientStatusPacket.h"
#include "ingame/clientbound/chunk/ServerChunkDataPacket.h"

namespace McProtocol {

PacketFactory::PacketFactory() {

}

PacketFactory::~PacketFactory() {

}

std::unique_ptr<Packet> PacketFactory::createServerBoundPacket(int id) {
  if (status_ == ProtocolStatus::HANDSHAKE) {
    switch (id) {
      case 0x00:return std::unique_ptr<Packet>(new HandshakePacket());
      default: return nullptr;
    }
  } else if (status_ == ProtocolStatus::STATUS) {
    switch (id) {
      case 0x00:return std::unique_ptr<Packet>(new StatusRequestPacket());
      case 0x01:return std::unique_ptr<Packet>(new StatusPingPacket());
      default:return nullptr;
    }
  } else if (status_ == ProtocolStatus::LOGIN) {
    switch (id) {
      case 0x00:return std::unique_ptr<Packet>(new LoginStartPacket());
      default:return nullptr;
    }
  } else if (status_ == ProtocolStatus::PLAY) {
    switch (id) {
      case 0x0F:return std::unique_ptr<Packet>(new ClientKeepAlivePacket());
      case 0x04:return std::unique_ptr<Packet>(new ClientStatusPacket());
      default:return nullptr;
    }
  } else {
    return nullptr;
  }
}

std::unique_ptr<Packet> PacketFactory::createClientBoundPacket(int id) {
  if (status_ == ProtocolStatus::STATUS) {
    switch (id) {
      case 0x00: return std::unique_ptr<Packet>(new StatusResponsePacket());
      case 0x01:return std::unique_ptr<Packet>(new StatusPongPacket());
      default:return nullptr;
    }
  } else if (status_ == ProtocolStatus::LOGIN) {
    switch (id) {
      case 0x02:return std::unique_ptr<Packet>(new LoginSuccessPacket());
      case 0x03:return std::unique_ptr<Packet>(new SetCompressionPacket());
      default:return nullptr;
    }
  } else if (status_ == ProtocolStatus::PLAY) {
    switch (id) {
      case 0x21:return std::unique_ptr<Packet>(new ServerKeepAlivePacket());
      case 0x22:return std::unique_ptr<Packet>(new ServerChunkDataPacket());
      default:return nullptr;
    }
  } else {
    return nullptr;
  }
}
}