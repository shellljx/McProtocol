//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class SetCompressionPacket : public Packet {
 public:
  SetCompressionPacket();
  ~SetCompressionPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  int getCompressionThreshold() const {
    return threshold;
  }
 private:
  int threshold;
};
}