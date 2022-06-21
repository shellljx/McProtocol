//
// Created by 李金祥 on 2022/6/11.
//

#include "TagDouble.h"
namespace McProtocol {
TagDouble::TagDouble(const std::string &name) : Tag(name) {

}

TagDouble::~TagDouble() = default;

void TagDouble::write(EncodeStream *stream) {

}

void TagDouble::read(DecodeStream *stream) {
  value_ = stream->readDouble();
}

TagType TagDouble::getType() {
  return TagType::Double;
}
}