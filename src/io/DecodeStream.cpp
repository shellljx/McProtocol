//
// Created by 李金祥 on 2022/5/28.
//

#include "DecodeStream.h"

namespace McProtocol {

ByteOrder DecodeStream::order() const {
  return order_;
}

void DecodeStream::setOrder(ByteOrder order) {
  order_ = order;
}

void DecodeStream::setPosition(uint32_t value) {
  if (value < length_) {
    position_ = value;
  } else {
    throw std::runtime_error("decode stream was encountered.");
  }
}

void DecodeStream::skip(uint32_t bytes) {
  if (position_ < length_ - bytes + 1) {
    position_ += bytes;
  } else {
    throw std::runtime_error("decode stream was encountered.");
  }
}

int DecodeStream::readVerInt() {
  int value = 0;
  int position = 0;
  uint8_t currentByte;

  while (true) {
    currentByte = readUint8();
    value |= (currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0) break;
    position += 7;
    if (position >= 32) throw std::runtime_error("varint is too big");
  }
  return value;
}

std::string DecodeStream::readUTF8String() {
  if (position_ < length_) {
    uint32_t textLength = readVerInt();
    auto text = reinterpret_cast<const char *>(bytes_ + position_);
    if (textLength > length_ - position_) {
      textLength = length_ - position_;
      position_ += textLength;
    }
    position_ += textLength;
    return std::string(text, textLength);
  }
  return "";
}

DecodeStream DecodeStream::readBytes(uint32_t length) {
  if (length > length_) {
    length = length_;
  }
  if (length > length_ - position_) {
    length = length_ - position_;
  }
  return {bytes_ + position_, length};
}

Bit8 DecodeStream::readBit8() {
  Bit8 data = {};
  if (position_ < length_) {
    data.uintValue = bytes_[position_++];
    return data;
  } else {
    throw std::runtime_error("decode stream readbit8 encountered.");
  }
}
}