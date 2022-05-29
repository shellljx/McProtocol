//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include <string>

namespace McProtocol {
class ByteData {
 public:
  static std::unique_ptr<ByteData> MakeCopy(const void *bytes, size_t length);
  static std::unique_ptr<ByteData> Make(size_t length);
  static std::unique_ptr<ByteData> MakeAdopted(uint8_t* data, size_t length);

  ~ByteData(){
    if (data_){
      delete[] data_;
    }
  };

  /**
   * returns the memory address of byte data.
   * @return
   */
  uint8_t *data() const {
    return data_;
  }

  /**
   * returns the byte size.
   * @return
   */
  size_t length() const {
    return length_;
  }

 private:
  ByteData(uint8_t *data, size_t length) : data_(data), length_(length) {
  }

 private:
  uint8_t *data_;
  size_t length_;
};
}
