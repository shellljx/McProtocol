//
// Created by 李金祥 on 2022/6/11.
//

#include "TagInt.h"
namespace McProtocol {
TagInt::TagInt(const std::string &name) : Tag(name) {

}

TagInt::~TagInt() = default;

void TagInt::write(EncodeStream *stream) {

}

void TagInt::read(DecodeStream *stream) {
  value_ = stream->readInt32();
}

TagType TagInt::getType() {
  return TagType::Int;
}
}