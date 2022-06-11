//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"
#include <vector>

namespace McProtocol {
class TagIntArray : public Tag {
 public:
  explicit TagIntArray(const std::string &name);
  ~TagIntArray() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  std::vector<int> values_;
};
}
