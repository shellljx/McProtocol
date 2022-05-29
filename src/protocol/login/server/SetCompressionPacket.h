//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class SetCompressionPacket : public Packet {
 public:
  SetCompressionPacket();
  ~SetCompressionPacket();

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

  int getCompressionThreshold() const {
    return threshold;
  }
 private:
  int threshold;
};
}