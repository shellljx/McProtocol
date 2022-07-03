//
// Created by 李金祥 on 2022/7/2.
//

#pragma once
#include "io/ByteData.h"
#include "file.h"

namespace McRenderer {
class Texture {
 public:
  explicit Texture(const std::string &name, int width, int height, int depth);
  ~Texture();

  void setLocation(Point location);

  Point getLocation() {
    return location_;
  }

  int getWidth() {
    return width_;
  }

  int getHeight() {
    return height_;
  }

  int getDepth() {
    return depth_;
  }

  std::string getName() {
    return name_;
  }

 private:
  std::string name_ = "";
  Point location_ = {0, 0};
  int width_ = 0;
  int height_ = 0;
  int depth_ = 0;
};
}
