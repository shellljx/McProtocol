//
// Created by 李金祥 on 2022/5/28.
//

#include "SizerCodec.h"
namespace McProtocol {

DecodeStream SizerCodec::decode(DecodeStream &in) {
  auto oldPosition = in.position();
  //check validate varint
  bool notVarint = false;
  for (int i = 0; i < 5; ++i) {
    if (in.bytesAvailable() == 0) {
      notVarint = true;
      break;
    }
    if (in.readInt8() >= 0) {
      break;
    }
  }
  in.setPosition(oldPosition);
  if (notVarint) {
    return {nullptr, 0};
  }
  auto packetLength = in.readVerInt();
  if (packetLength > 0 && packetLength <= in.bytesAvailable()) {
    return in.readBytes(packetLength);
  } else {
    in.setPosition(oldPosition);
    return {nullptr, 0};
  }
}
}