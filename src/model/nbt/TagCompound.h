//
// Created by 李金祥 on 2022/6/10.
//

#pragma once
#include "Tag.h"
#include <map>

namespace McProtocol {
class TagCompound : public Tag {
 public:
  explicit TagCompound(const std::string &name);
  ~TagCompound() override;

  static std::unique_ptr<TagCompound> Create(DecodeStream *stream);

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  std::map<std::string, std::shared_ptr<Tag>> tags;
};
}
