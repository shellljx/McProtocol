//
// Created by 李金祥 on 2022/6/22.
//

#pragma once
#include "renderer/file.h"
#include "nlohmann/json.hpp"
#include "FaceInfo.h"
#include <vector>

namespace McRenderer {
class Element {
 public:
  explicit Element(const nlohmann::json &json);
  ~Element();

  void replaceTexture(const std::string &key, const std::string &texture);

  Point3D getFrom() {
    return from_;
  }

  Point3D getTo() {
    return to_;
  }

  std::vector<std::shared_ptr<FaceInfo>> getFaces() {
    return faces_;
  }

 private:
  Point3D from_{};
  Point3D to_{};
  std::vector<std::shared_ptr<FaceInfo>> faces_;
};
}