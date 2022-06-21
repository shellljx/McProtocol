//
// Created by 李金祥 on 2022/6/17.
//

#pragma once
#include <array>
#include <vector>
#include "file.h"

namespace McRenderer{
class Face {
 public:
  explicit Face(const Orientation orientation,const std::vector<float> textures);
  ~Face();

 public:
  static const std::vector<float> botoom_face;
 private:
  //model matrix 16 floats
  std::array<float, 16> modelMatrix_;
  //(u1,v1,u2,v2)
  std::array<float, 4> textureCoords_;
};
}