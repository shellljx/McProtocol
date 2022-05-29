//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "../../Packet.h"

namespace McProtocol {
class StatusResponsePacket : public Packet{
 public:
  StatusResponsePacket();
  ~StatusResponsePacket();

  void read(DecodeStream* stream);
  void write(EncodeStream* stream);

  std::string getInfo() const{
    return info;
  }

 private:
  std::string info;
};
}