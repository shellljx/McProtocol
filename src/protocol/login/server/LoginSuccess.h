//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class LoginSuccessPacket : public Packet {
 public:
  LoginSuccessPacket();
  ~LoginSuccessPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  std::string getUUID() const {
    return uuid;
  }

  std::string getUserName() const {
    return userName;
  }
 private:
  std::string uuid = "";
  std::string userName = "";
};
}