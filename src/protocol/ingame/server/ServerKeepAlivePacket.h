//
// Created by 李金祥 on 2022/5/31.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class ServerKeepAlivePacket : public Packet {
 public:
  ServerKeepAlivePacket();
  ~ServerKeepAlivePacket();

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

  long getKeepAliveId() const {
    return keepAliveId_;
  }
 private:
  long long keepAliveId_;
};
}