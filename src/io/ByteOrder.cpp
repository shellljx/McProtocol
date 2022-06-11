//
// Created by 李金祥 on 2022/5/28.
//

#include "ByteOrder.h"

namespace McProtocol {
ByteOrder EndianTest() {
  int i = 1;
  auto p = static_cast<char*>(static_cast<void*>(&i));
  return (*p == 1) ? ByteOrder::LittleEndian : ByteOrder::BigEndian;
}
}