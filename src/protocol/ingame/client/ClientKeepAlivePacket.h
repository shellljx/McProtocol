//
// Created by 李金祥 on 2022/5/31.
//

#pragma once
#include "../../Packet.h"
namespace McProtocol {
class ClientKeepAlivePacket : public Packet {
 public:
  ClientKeepAlivePacket();
  ~ClientKeepAlivePacket();

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

  long getKeepAliveId() const {
    return keepAliveId_;
  }

  void setKeepAliveId(long id) {
    keepAliveId_ = id;
  }
 private:
  long long keepAliveId_;
};
}