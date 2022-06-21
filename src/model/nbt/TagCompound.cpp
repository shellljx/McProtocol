//
// Created by 李金祥 on 2022/6/10.
//

#include "TagCompound.h"

namespace McProtocol {
TagCompound::TagCompound(const std::string &name) : Tag(name) {

}

TagCompound::~TagCompound() = default;

std::unique_ptr<TagCompound> TagCompound::Create(DecodeStream *stream) {
  const auto type = (TagType) stream->readInt8();
  if (type == TagType::Compound) {
    const auto name = stream->readUtfString();
    auto tagCompound = new TagCompound(name);
    tagCompound->read(stream);
    return std::unique_ptr<TagCompound>(tagCompound);
  }
  return nullptr;
}

void TagCompound::read(DecodeStream *stream) {
  while (true) {
    const auto type = (TagType) stream->readInt8();

    if (type == TagType::End) {
      break;
    }

    const std::string name = stream->readUtfString();
    auto tag = Tag::CreateTag(type, name);
    tag->read(stream);
    tags[name] = tag;
  }
}

void TagCompound::write(EncodeStream *stream) {

}

TagType TagCompound::getType() {
  return TagType::Compound;
}
}