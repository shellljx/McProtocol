//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"
#include <vector>

namespace McProtocol {
class TagList : public Tag {
 public:
  explicit TagList(const std::string &name);
  ~TagList() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  std::vector<std::shared_ptr<Tag>> tags_;
  TagType tag_type_;
};
}
