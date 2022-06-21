//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace McProtocol {
class TagShort : public Tag {
 public:
  explicit TagShort(const std::string &name);
  ~TagShort() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  short value_;
};
}
