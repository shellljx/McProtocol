//
// Created by 李金祥 on 2022/6/7.
//

#pragma once
#include "Section.h"
#include <vector>

namespace McProtocol {
class Column {

 private:
  int x;
  int z;
  std::vector<std::unique_ptr<Section>> sections;
};
}
