//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace McProtocol {
class TagInt : public Tag {
 public:
  explicit TagInt(const std::string &name);
  ~TagInt() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  int value_;
};
}
