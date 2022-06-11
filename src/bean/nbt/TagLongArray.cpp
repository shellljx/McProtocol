//
// Created by 李金祥 on 2022/6/11.
//

#include "TagLongArray.h"
namespace McProtocol {
TagLongArray::TagLongArray(const std::string &name) : Tag(name) {

}

TagLongArray::~TagLongArray() = default;

void TagLongArray::write(EncodeStream *stream) {

}

void TagLongArray::read(DecodeStream *stream) {
  const auto count = stream->readInt32();
  value_ = std::vector<long long>(count);
  for (int i = 0; i < count; ++i) {
    value_[i] = stream->readInt64();
  }
}

TagType TagLongArray::getType() {
  return TagType::LongArray;
}
}