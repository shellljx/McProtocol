//
// Created by 李金祥 on 2022/6/11.
//

#include "TagLong.h"
namespace McProtocol {
TagLong::TagLong(const std::string &name) : Tag(name) {

}

TagLong::~TagLong() = default;

void TagLong::write(EncodeStream *stream) {

}

void TagLong::read(DecodeStream *stream) {
  value_ = stream->readInt64();
}

TagType TagLong::getType() {
  return TagType::Long;
}
}