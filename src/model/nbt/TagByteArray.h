//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace McProtocol {
class TagByteArray : public Tag {
 public:
  explicit TagByteArray(const std::string &name);
  ~TagByteArray() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  std::unique_ptr<ByteData> byte_data_;
};
}
