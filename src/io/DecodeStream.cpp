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
  if ((length_ >= length) && (position_ <= length_ - length)) {
    DecodeStream stream(bytes_ + position_, length);
    position_ += length;
    return stream;
  } else {
    throw std::runtime_error("readBytes was encountered.");
  }
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

Bit32 DecodeStream::readBit32() {
  Bit32 data = {};
  if ((length_ > 3) && (position_ < length_ - 3)) {
    if (order_ == ByteOrder::BigEndian) {
      for (int i = 0; i < 4; i++) {
        data.bytes[i] = bytes_[position_++];
      }
    } else {
      for (int i = 3; i >= 0; i--) {
        data.bytes[i] = bytes_[position_++];
      }
    }
  }
}

Bit64 DecodeStream::readBit64() {
  Bit64 data = {};
  if ((length_ > 7) && (position_ < length_ - 7)) {
    if (order_ == ByteOrder::BigEndian) {
      for (int i = 0; i < 8; ++i) {
        data.bytes[i] = bytes_[position_++];
      }
    } else {
      for (int i = 7; i >= 0; i--) {
        data.bytes[i] = bytes_[position_++];
      }
    }
  } else {
    throw std::runtime_error("readBit64 was encountered.");
  }
  return data;
}
}