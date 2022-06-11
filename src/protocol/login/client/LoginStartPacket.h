//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class LoginStartPacket : public Packet {
 public:
  LoginStartPacket();
  ~LoginStartPacket() override;

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

  void setUserName(std::string &name) {
    userName = name;
  }
 private:
  std::string userName = "protocol_player";
};
}