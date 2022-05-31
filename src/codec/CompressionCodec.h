//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "../io/EncodeStream.h"
#include "../io/DecodeStream.h"

namespace McProtocol{
class CompressionCodec {
 public:
  std::unique_ptr<ByteData> decode(DecodeStream& in);

  void setEnable(bool enable){
    enable_ = enable;
  }

 private:
  std::unique_ptr<McProtocol::ByteData> deCompression(DecodeStream & in, int uLength);
 private:
  bool enable_ = false;
};
}
