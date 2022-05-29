//
// Created by 李金祥 on 2022/5/28.
//

#pragma once

#include "ByteData.h"
#include "ByteOrder.h"

namespace McProtocol {
class EncodeStream final {
 public:
  explicit EncodeStream(uint32_t capacity = 128);
  ~EncodeStream();

  /**
   * This EncodeStream's byte order. The byte order is used when reading or writing multibyte values.
   * The order of a newly created stream is always ByteOrder::LittleEndian
   * @return
   */
  ByteOrder order() const;

  void setOrder(ByteOrder order);

  uint32_t length() const {
    return length_;
  }

  uint32_t position() const {
    return position_;
  }

  void setPosition(uint32_t value) {
    position_ = value;
    positionChanged();
  }

  void writeBytes(EncodeStream *stream, uint32_t length = 0, uint32_t offset = 0);

  void writeBytes(const uint8_t *stream, uint32_t length, uint32_t offset = 0);

  void writeByteData(const ByteData *byteData);

  void writeInt8(int8_t value);

  void writeUint8(uint8_t value);

  void writeBoolean(bool value);

  void writeInt16(int16_t value);

  void writeUInt16(uint16_t value);

  void writeVarInt(int value);
  void writeUTF8String(const std::string &text);

  /**
   * Take ownership of the current bytes. Once the release method is called, the EncodeStream object will be
   * reset to a new one, and the returned bytes will be managed by the ByteData object
   * @return
   */
  std::unique_ptr<ByteData> release();

 private:
  void ensureCapacity(uint32_t length) {
    if (length > capacity_) {
      expandCapacity(capacity_);
    }
  }

  void positionChanged() {
    if (position_ > length_) {
      length_ = position_;
    }
  }

  void expandCapacity(uint32_t length);
  void writeBit8(Bit8 data);
  void writeBit16(Bit16 data);

 private:
  ByteOrder order_ = ByteOrder::LittleEndian;
  uint8_t *bytes_ = nullptr;
  uint32_t capacity_ = 0;
  uint32_t length_ = 0;
  uint32_t position_ = 0;
};
}