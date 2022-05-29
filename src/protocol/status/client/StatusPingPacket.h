//
// Created by 李金祥 on 2022/5/29.
//
#pragma once
#include "../../Packet.h"
namespace McProtocol {
class StatusPingPacket : public Packet {
 public:
  StatusPingPacket();
  ~StatusPingPacket();

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

  void setPayload(long payload) {
    pingTime = payload;
  }

  long getPayload() {
    return pingTime;
  }

 private:
  long pingTime;
};
}