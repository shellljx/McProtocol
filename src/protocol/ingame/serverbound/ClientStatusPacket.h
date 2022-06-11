//
// Created by 李金祥 on 2022/5/31.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class ClientStatusPacket : public Packet {
 public:
  ClientStatusPacket();
  ~ClientStatusPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  void setAction(int action) {
    action_ = action;
  }

  int getAction() {
    return action_;
  }

 private:
  int action_ = 0;
};
}