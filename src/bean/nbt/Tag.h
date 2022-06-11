//
// Created by 李金祥 on 2022/6/10.
//

#pragma once
#include "io/ReadWriteable.h"

namespace McProtocol {

enum class TagType {
  End = 0,
  Byte,
  Short,
  Int,
  Long,
  Float,
  Double,
  ByteArray,
  String,
  List,
  Compound,
  IntArray,
  LongArray
};

class Tag : public ReadWriteable {
 public:
  explicit Tag(const std::string &name) {
    this->name = name;
  }
  ~Tag() override = default;

  static std::shared_ptr<Tag> CreateTag(const TagType type, const std::string &name);

  virtual TagType getType() = 0;

 private:
  std::string name;
};
}