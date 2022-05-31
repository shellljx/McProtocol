//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include <string>

namespace McProtocol {
class ByteData {
 public:
  static std::unique_ptr<ByteData> MakeCopy(const void *bytes, size_t length);
  static std::unique_ptr<ByteData> MakeWithoutCopy(const uint8_t *data, size_t length);
  static std::unique_ptr<ByteData> Make(size_t length);
  static std::unique_ptr<ByteData> MakeAdopted(uint8_t *data, size_t length);

  ~ByteData() {
    if (releaseCallback_) {
      releaseCallback_(data_);
    }
  };

  /**
   * returns the memory address of byte data.
   * @return
   */
  const uint8_t *data() const {
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
  static void DeleteCallback(const uint8_t *data) {
    delete[] data;
  }
  ByteData(const uint8_t *data, size_t length, std::function<void(const uint8_t *)> releaseCallback = DeleteCallback)
      : data_(data), length_(length), releaseCallback_(std::move(releaseCallback)) {
  }

 private:
  const uint8_t *data_;
  size_t length_;
  const std::function<void(const uint8_t *)> releaseCallback_;
};
}
