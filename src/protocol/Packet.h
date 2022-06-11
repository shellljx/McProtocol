//
// Created by 李金祥 on 2022/5/28.
//
#pragma once
#include "../io/ReadWriteable.h"

namespace McProtocol {
class Packet : public ReadWriteable {
 public:
  Packet(int packetId) : packetId_(packetId) {

  }
  ~Packet() override = default;

  void read(DecodeStream *stream) override = 0;
  void write(EncodeStream *stream) override = 0;

  int getPacketId() const {
    return packetId_;
  }

 private:
  int packetId_;
};
}