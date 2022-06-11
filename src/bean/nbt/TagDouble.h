//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace McProtocol {
class TagDouble : public Tag {
 public:
  explicit TagDouble(const std::string &name);
  ~TagDouble() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  double value_;
};
}
