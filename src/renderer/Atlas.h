//
// Created by 李金祥 on 2022/6/18.
//

#pragma once
#include <map>
#include "io/ByteData.h"
#include "file.h"
#include "Texture.h"

namespace McRenderer {

class Atlas {
 public:
  explicit Atlas();
  ~Atlas();

  void pack2DTexture(const std::vector<std::string> &paths, bool save);

  std::shared_ptr<Texture> getTexture(const std::string &name);

  const unsigned char *getDatas() {
    return datas_->data();
  }

  int getWidth() const {
    return width_;
  }

  int getHeight() const {
    return height_;
  }

 private:
  std::map<std::string, std::shared_ptr<Texture>> textureMap_;
  std::unique_ptr<McProtocol::ByteData> datas_;
  int width_ = 0;
  int height_ = 0;
};
}
