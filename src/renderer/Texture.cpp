//
// Created by 李金祥 on 2022/7/2.
//

#include "Texture.h"

namespace McRenderer {
Texture::Texture(const std::string &name, int width, int height, int depth) {
  name_ = name;
  width_ = width;
  height_ = height;
  depth_ = depth;
}

Texture::~Texture() = default;

void Texture::setLocation(Point location) {
  location_ = location;
}

}