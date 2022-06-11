//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "../Packet.h"

namespace McProtocol {
class HandshakePacket : public Packet{
 public:
  HandshakePacket();
  ~HandshakePacket() override;

  void read(DecodeStream* stream) override;
  void write(EncodeStream* stream) override;

 private:
  int protocolVersion_ = 758;
  std::string serverAddr_ = "127.0.0.1";
  int16_t serverPort = 25565;
  int intent = 2;
};
}