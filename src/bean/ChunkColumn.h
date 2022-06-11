//
// Created by 李金祥 on 2022/6/7.
//

#pragma once
#include "ChunkSection.h"
#include <vector>

namespace McProtocol {
class ChunkColumn {

 private:
  int x;
  int z;
  std::vector<std::unique_ptr<ChunkSection>> sections;
};
}
