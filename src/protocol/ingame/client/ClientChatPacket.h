//
// Created by 李金祥 on 2022/6/1.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class ClientChatPacket : public Packet {
 public:
  ClientChatPacket(const char *message);
  ~ClientChatPacket();

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

 private:
  std::string message_;
};
}