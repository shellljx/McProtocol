//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include <cinttypes>

#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

namespace McProtocol {
enum class ByteOrder {LittleEndian, BigEndian};

union Bit8 {
  int8_t intValue;
  uint8_t uintValue;
  bool boolValue;
};

union Bit16 {
  uint8_t bytes[2];
  int16_t intValue;
  uint16_t uintValue;
};

union Bit32 {
  uint8_t bytes[4];
  int32_t intValue;
  uint32_t uintValue;
  float floatValue;
};

union Bit64 {
  uint8_t bytes[8];
  int64_t intValue;
  uint64_t uintValue;
  double doubleValue;
};
}

