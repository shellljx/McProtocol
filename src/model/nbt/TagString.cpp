//
// Created by 李金祥 on 2022/6/11.
//

#include "TagString.h"
namespace McProtocol {
TagString::TagString(const std::string &name) : Tag(name) {

}

TagString::~TagString() = default;

void TagString::write(EncodeStream *stream) {

}

void TagString::read(DecodeStream *stream) {
  value_ = stream->readUtfString();
}

TagType TagString::getType() {
  return TagType::String;
}
}