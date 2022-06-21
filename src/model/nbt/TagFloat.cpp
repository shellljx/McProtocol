//
// Created by 李金祥 on 2022/6/11.
//

#include "TagFloat.h"
namespace McProtocol {
TagFloat::TagFloat(const std::string &name) : Tag(name) {

}

TagFloat::~TagFloat() = default;

void TagFloat::write(EncodeStream *stream) {

}

void TagFloat::read(DecodeStream *stream) {
  value_ = stream->readFloat();
}

TagType TagFloat::getType() {
  return TagType::Float;
}
}