//
// Created by 李金祥 on 2022/6/11.
//

#include "LightUpdateData.h"
namespace McProtocol {
LightUpdateData::LightUpdateData() {
}

LightUpdateData::~LightUpdateData() = default;

void LightUpdateData::write(EncodeStream *stream) {

}

void LightUpdateData::read(DecodeStream *stream) {
  trustEdges_ = stream->readBoolean();

  const int skyYMaskSize = stream->readVarInt();
  skyYMask_ = std::vector<unsigned long long int>(skyYMaskSize);
  for (int i = 0; i < skyYMaskSize; ++i) {
    skyYMask_[i] = stream->readUint64();
  }

  const int blockYMaskSize = stream->readVarInt();
  blockYMask_ = std::vector<unsigned long long int>(blockYMaskSize);
  for (int i = 0; i < blockYMaskSize; ++i) {
    blockYMask_[i] = stream->readUint64();
  }

  const int emptySkyYMaskSize = stream->readVarInt();
  emptySkyYMask_ = std::vector<unsigned long long int>(emptySkyYMaskSize);
  for (int i = 0; i < emptySkyYMaskSize; ++i) {
    emptySkyYMask_[i] = stream->readUint64();
  }

  const int emptyBlockYMaskSize = stream->readVarInt();
  emptyBlockYMask_ = std::vector<unsigned long long int>(emptyBlockYMaskSize);
  for (int i = 0; i < emptyBlockYMaskSize; ++i) {
    emptyBlockYMask_[i] = stream->readUint64();
  }

  const int skyUpdateSize = stream->readVarInt();
  skyUpdates_ = std::vector<std::unique_ptr<ByteData>>(skyUpdateSize);
  for (int i = 0; i < skyUpdateSize; ++i) {
    //2048
    const int length = stream->readVarInt();
    skyUpdates_[i] = stream->readByteData(length);
  }

  const int blockUpdateSize = stream->readVarInt();
  blockUpdates_ = std::vector<std::unique_ptr<ByteData>>(blockUpdateSize);
  for (int i = 0; i < blockUpdateSize; ++i) {
    //2048
    const int length = stream->readVarInt();
    blockUpdates_[i] = stream->readByteData(length);
  }
}
}