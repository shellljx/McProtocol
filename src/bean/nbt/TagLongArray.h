//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"
#include <vector>

namespace McProtocol {
class TagLongArray : public Tag {
 public:
  explicit TagLongArray(const std::string &name);
  ~TagLongArray() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  std::vector<long long> value_;
};
}
