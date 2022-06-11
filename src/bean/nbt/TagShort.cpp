//
// Created by 李金祥 on 2022/6/11.
//

#include "TagShort.h"
namespace McProtocol {
TagShort::TagShort(const std::string &name) : Tag(name) {

}

TagShort::~TagShort() = default;

void TagShort::write(EncodeStream *stream) {

}

void TagShort::read(DecodeStream *stream) {
  value_ = stream->readInt16();
}

TagType TagShort::getType() {
  return TagType::Short;
}
}