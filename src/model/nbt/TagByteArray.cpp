//
// Created by 李金祥 on 2022/6/11.
//

#include "TagByteArray.h"

namespace McProtocol {
TagByteArray::TagByteArray(const std::string &name) : Tag(name) {

}

TagByteArray::~TagByteArray() = default;

void TagByteArray::write(EncodeStream *stream) {

}

void TagByteArray::read(DecodeStream *stream) {
  auto length = stream->readInt32();
  byte_data_ = stream->readByteData(length);
}

TagType TagByteArray::getType() {
  return TagType::ByteArray;
}
}