//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "../../Packet.h"

namespace McProtocol {
class StatusRequestPacket : public Packet{
 public:
  StatusRequestPacket();
  ~StatusRequestPacket() override;

  void read(DecodeStream* stream) override;
  void write(EncodeStream* stream) override;
};
}