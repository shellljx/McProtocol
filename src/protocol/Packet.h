//
// Created by 李金祥 on 2022/5/28.
//
#pragma once
#include "../io/DecodeStream.h"
#include "../io/EncodeStream.h"

namespace McProtocol {
class Packet {
 public:
  Packet(int packetId) : packetId_(packetId) {

  }
  virtual ~Packet() {
  };

  virtual void read(DecodeStream *stream) = 0;
  virtual void write(EncodeStream *stream) = 0;

  int getPacketId() const {
    return packetId_;
  }

 private:
  int packetId_;
};
}