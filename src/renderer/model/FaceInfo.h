//
// Created by 李金祥 on 2022/6/22.
//

#pragma once
#include "nlohmann/json.hpp"
#include "renderer/file.h"

namespace McRenderer {
class FaceInfo {
 public:
  explicit FaceInfo(Orientation orientation, const nlohmann::json &json);
  ~FaceInfo();

  void replaceTexture(const std::string &key, const std::string &texture);
  Orientation getOrientation() {
    return orientation_;
  }

 private:
  Orientation orientation_ = Orientation::None;
  Point uvStart_{};
  Point uvEnd_{};
  std::string texture_;
};
}
