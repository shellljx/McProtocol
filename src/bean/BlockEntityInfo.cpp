//
// Created by 李金祥 on 2022/6/11.
//

#include "BlockEntityInfo.h"

namespace McProtocol {
BlockEntityInfo::BlockEntityInfo() {
}

BlockEntityInfo::~BlockEntityInfo() = default;

void BlockEntityInfo::write(EncodeStream *stream) {

}

void BlockEntityInfo::read(DecodeStream *stream) {
  int8_t xz = stream->readInt8();
  int blockEntityX = (xz >> 4) & 15;
  int blockEntityZ = xz & 15;
  int blockEntityY = stream->readInt16();
  type_ = stream->readVarInt();
  //nbt
  nbt_ = TagCompound::Create(stream);
}
}