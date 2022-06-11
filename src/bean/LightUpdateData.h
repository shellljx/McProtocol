//
// Created by 李金祥 on 2022/6/11.
//
#pragma once
#include <vector>
#include "io/ReadWriteable.h"

namespace McProtocol {
class LightUpdateData : public ReadWriteable {
 public:
  LightUpdateData();
  ~LightUpdateData() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::vector<unsigned long long int> skyYMask_;
  std::vector<unsigned long long int> blockYMask_;
  std::vector<unsigned long long int> emptySkyYMask_;
  std::vector<unsigned long long int> emptyBlockYMask_;

  std::vector<std::unique_ptr<ByteData>> skyUpdates_;
  std::vector<std::unique_ptr<ByteData>> blockUpdates_;
  bool trustEdges_;
};
}