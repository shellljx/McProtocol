//
// Created by 李金祥 on 2022/6/11.
//

#include "TagList.h"
namespace McProtocol {
TagList::TagList(const std::string &name) : Tag(name) {

}

TagList::~TagList() = default;

void TagList::write(EncodeStream *stream) {

}

void TagList::read(DecodeStream *stream) {
  tag_type_ = (TagType) stream->readInt8();
  const int count = stream->readInt32();

  tags_ = std::vector<std::shared_ptr<Tag>>(count);

  if (tag_type_ == TagType::End) {
    return;
  }

  for (int i = 0; i < count; ++i) {
    tags_[i] = Tag::CreateTag(tag_type_, "");
    tags_[i]->read(stream);
  }
}

TagType TagList::getType() {
  return TagType::List;
}
}