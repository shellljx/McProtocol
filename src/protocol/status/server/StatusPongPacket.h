//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class StatusPongPacket : public Packet {
 public:
  StatusPongPacket();
  ~StatusPongPacket();

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

  long getPayload(){
    return pingTime;
  }

 private:
  long pingTime = 0;
};
}