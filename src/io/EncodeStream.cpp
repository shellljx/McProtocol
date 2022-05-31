//
// Created by 李金祥 on 2022/5/28.
//

#include "EncodeStream.h"

namespace McProtocol {
EncodeStream::EncodeStream(uint32_t capacity) {
  capacity_ = capacity;
  bytes_ = new uint8_t[capacity];
}

EncodeStream::~EncodeStream() {
  delete[] bytes_;
}

ByteOrder EncodeStream::order() const {
  return order_;
}

void EncodeStream::setOrder(ByteOrder order) {
  order_ = order;
}

std::unique_ptr<ByteData> EncodeStream::release() {
  auto data = ByteData::MakeAdopted(bytes_, length_);
  capacity_ = 256;
  position_ = 0;
  length_ = 0;
  bytes_ = new uint8_t[capacity_];
  return data;
}

void EncodeStream::writeBytes(EncodeStream *stream, uint32_t length, uint32_t offset) {
  if (stream->length_ <= offset) {
    return;
  }

  if (length == 0) {
    length = stream->length_ - offset;
  }
  writeBytes(stream->bytes_, length, offset);
}

void EncodeStream::writeBytes(const uint8_t *stream, uint32_t length, uint32_t offset) {
  ensureCapacity(position_ + length);
  memcpy(bytes_ + position_, stream + offset, length);
  position_ += length;
  positionChanged();
}

void EncodeStream::writeByteData(const ByteData *byteData) {
  if (byteData == nullptr) {
    return;
  }
  auto length = static_cast<uint32_t>(byteData->length());
  writeBytes(byteData->data(), length);
}

void EncodeStream::writeBoolean(bool value) {
  Bit8 data = {};
  data.boolValue = value;
  writeBit8(data);
}

void EncodeStream::writeInt8(int8_t value) {
  Bit8 data = {};
  data.intValue = value;
  writeBit8(data);
}

void EncodeStream::writeUint8(uint8_t value) {
  ensureCapacity(position_ + 1);
  bytes_[position_++] = value;
  positionChanged();
}

void EncodeStream::writeInt16(int16_t value) {
  Bit16 data = {};
  data.intValue = value;
  writeBit16(data);
}

void EncodeStream::writeUInt16(uint16_t value) {
  Bit16 data = {};
  data.uintValue = value;
  writeBit16(data);
}

void EncodeStream::writeUint32(uint32_t value) {
  Bit32 data = {};
  data.uintValue = value;
  writeBit32(data);
}

void EncodeStream::writeInt32(int32_t value) {
  ensureCapacity(position_ + 4);
  if (order_ == ByteOrder::BigEndian) {
    for (int i = 0; i < 4; i++) {
      bytes_[position_++] = value >> i * 8;
    }
  } else {
    for (int i = 3; i >= 0; i--) {
      bytes_[position_++] = value >> i * 8;
    }
  }
  positionChanged();
}

void EncodeStream::writeInt64(int64_t value) {
  Bit64 data = {};
  data.intValue = value;
  writeBit64(data);
}

void EncodeStream::writeUInt64(uint64_t value) {
  Bit64 data = {};
  data.uintValue = value;
  writeBit64(data);
}

void EncodeStream::writeDouble(double value) {
  Bit64 data = {};
  data.doubleValue = value;
  writeBit64(data);
}

void EncodeStream::writeVarInt(int value) {
  unsigned int uValue = value;
  while (true) {
    if ((uValue & ~SEGMENT_BITS) == 0) {
      writeUint8(uValue);
      return;
    }
    writeUint8((uValue & SEGMENT_BITS) | CONTINUE_BIT);
    uValue >>= 7;
  }
}

void EncodeStream::writeUTF8String(const std::string &text) {
  auto size = static_cast<int>(text.size());
  if (size > 32767) {
    throw std::runtime_error("string was too big, max 32767");
  }
  writeVarInt(size);
  ensureCapacity(position_ + size);
  memcpy(bytes_ + position_, text.c_str(), size);
  position_ += size;
  positionChanged();
}

void EncodeStream::expandCapacity(uint32_t length) {
  while (capacity_ < length) {
    capacity_ = static_cast<uint32_t>(capacity_ * 1.5);
  }
  auto newBytes = new uint8_t[capacity_];
  memcpy(newBytes, bytes_, length_);
  delete[] bytes_;
  bytes_ = newBytes;
}

void EncodeStream::writeBit8(Bit8 data) {
  ensureCapacity(position_ + 1);
  if (bytes_ != nullptr) {
    bytes_[position_++] = data.uintValue;
  }
  positionChanged();
}

void EncodeStream::writeBit16(Bit16 data) {
  ensureCapacity(position_ + 2);
  if (order_ == ByteOrder::BigEndian) {
    bytes_[position_++] = data.bytes[0];
    bytes_[position_++] = data.bytes[1];
  } else {
    bytes_[position_++] = data.bytes[1];
    bytes_[position_++] = data.bytes[0];
  }
  positionChanged();
}

void EncodeStream::writeBit32(Bit32 data) {
  ensureCapacity(position_ + 4);
  if (order_ == ByteOrder::BigEndian) {
    for (int i = 0; i < 4; i++) {
      bytes_[position_++] = data.bytes[i];
    }
  } else {
    for (int i = 3; i >= 0; i--) {
      bytes_[position_++] = data.bytes[i];
    }
  }
  positionChanged();
}

void EncodeStream::writeBit64(Bit64 data) {
  ensureCapacity(position_ + 8);
  if (order_ == ByteOrder::BigEndian) {
    for (int i = 0; i < 8; i++) {
      bytes_[position_++] = data.bytes[i];
    }
  } else {
    for (int i = 7; i >= 0; i--) {
      bytes_[position_++] = data.bytes[i];
    }
  }
  positionChanged();
}
}