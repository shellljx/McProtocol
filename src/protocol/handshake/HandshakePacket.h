//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "../Packet.h"

namespace McProtocol {
class HandshakePacket : public Packet{
 public:
  HandshakePacket();
  ~HandshakePacket();

  void read(DecodeStream* stream);
  void write(EncodeStream* stream);

 private:
  int protocolVersion_ = 756;
  std::string serverAddr_ = "127.0.0.1";
  int16_t serverPort = 25565;
  int intent = 2;
};
}