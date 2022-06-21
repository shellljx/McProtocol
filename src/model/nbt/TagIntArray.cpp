//
// Created by 李金祥 on 2022/6/11.
//

#include "TagIntArray.h"
namespace McProtocol {
TagIntArray::TagIntArray(const std::string &name) : Tag(name) {

}

TagIntArray::~TagIntArray() = default;

void TagIntArray::write(EncodeStream *stream) {

}

void TagIntArray::read(DecodeStream *stream) {
  const auto count = stream->readInt32();
  for (int i = 0; i < count; ++i) {
    values_.push_back(stream->readInt32());
  }
}

TagType TagIntArray::getType() {
  return TagType::IntArray;
}
}