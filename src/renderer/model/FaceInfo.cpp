//
// Created by 李金祥 on 2022/6/22.
//

#include "FaceInfo.h"
namespace McRenderer {
FaceInfo::FaceInfo(Orientation orientation, const nlohmann::json &json) {
  orientation_ = orientation;
  if (json.contains("uv")) {
    auto uv = json.at("uv");
    uvStart_ = {uv[0].get<float>(), uv[1].get<float>()};
    uvEnd_ = {uv[2].get<float>(), uv[3].get<float>()};
  } else {
    uvStart_ = {0, 0};
    uvEnd_ = {16, 16};
  }
  if (json.contains("texture")) {
    texture_ = json.at("texture");
  }
}

FaceInfo::~FaceInfo() {

}

void FaceInfo::replaceTexture(const std::string &key, const std::string &texture) {
  if (!strcmp(texture_.c_str(), ("#" + key).c_str())) {
    texture_ = texture;
  }
}
}