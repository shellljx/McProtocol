//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace McProtocol {
class TagByte : public Tag {
 public:
  explicit TagByte(const std::string &name);
  ~TagByte() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  char value_;
};
}
