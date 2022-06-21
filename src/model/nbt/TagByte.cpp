//
// Created by 李金祥 on 2022/6/11.
//

#include "TagByte.h"

namespace McProtocol {
TagByte::TagByte(const std::string &name) : Tag(name), value_(0) {

}

TagByte::~TagByte() = default;

void TagByte::write(EncodeStream *stream) {
}

void TagByte::read(DecodeStream *stream) {
  value_ = stream->readInt8();
}

TagType TagByte::getType() {
  return TagType::Byte;
}
}