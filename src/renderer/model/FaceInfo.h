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

  [[nodiscard]] Orientation getOrientation() const {
    return orientation_;
  }

  [[nodiscard]] std::string getTexture() const {
    return texture_;
  }

  PointF getUvStart() const {
    return uvStart_;
  }

  PointF getUvEnd() const {
    return uvEnd_;
  }

 private:
  Orientation orientation_ = Orientation::None;
  PointF uvStart_{};
  PointF uvEnd_{};
  std::string texture_;
};
}
