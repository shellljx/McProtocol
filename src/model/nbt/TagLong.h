//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace McProtocol {
class TagLong : public Tag {
 public:
  explicit TagLong(const std::string &name);
  ~TagLong() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  long long value_;
};
}
