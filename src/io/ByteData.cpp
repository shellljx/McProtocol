//
// Created by 李金祥 on 2022/5/28.
//

#include "ByteData.h"

namespace McProtocol {
std::unique_ptr<ByteData> ByteData::MakeCopy(const void *bytes, size_t length) {
  if (length == 0) {
    return Make(0);
  }
  auto data = new(std::nothrow) uint8_t[length];
  if (data == nullptr) {
    return nullptr;
  }
  memcpy(data, bytes, length);
  return std::unique_ptr<ByteData>(new ByteData(data, length));
}

std::unique_ptr<ByteData> ByteData::MakeWithoutCopy(const uint8_t *data, size_t length) {
  if (length == 0) {
    return Make(0);
  }
  auto byteData = new ByteData(data, length, nullptr);
  return std::unique_ptr<ByteData>(byteData);
}

std::unique_ptr<ByteData> ByteData::Make(size_t length) {
  auto data = length > 0 ? new(std::nothrow) uint8_t[length] : nullptr;
  auto byteData = new ByteData(data, length);
  return std::unique_ptr<ByteData>(byteData);
}

std::unique_ptr<ByteData> ByteData::MakeAdopted(uint8_t *data, size_t length) {
  if (length == 0) {
    return nullptr;
  }

  auto byteData = new ByteData(data, length);
  return std::unique_ptr<ByteData>(byteData);
}
}