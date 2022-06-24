//
// Created by 李金祥 on 2022/6/22.
//

#include "Element.h"
namespace McRenderer {
Element::Element(const nlohmann::json &json) {
  if (json.contains("from")) {
    auto from = json.at("from");
    from_ = {from[0].get<float>(), from[1].get<float>(), from[2].get<float>()};
  }
  if (json.contains("to")) {
    auto to = json.at("to");
    to_ = {to[0].get<float>(), to[1].get<float>(), to[2].get<float>()};
  }
  if (json.contains("faces")) {
    auto faces = json.at("faces");
    for (const auto &item : faces.items()) {
      Orientation orientation = GetOrientation(item.key().c_str());
      if (orientation == Orientation::None) {
        continue;
      }
      faces_.push_back(std::unique_ptr<FaceInfo>(new FaceInfo(orientation, item.value())));
    }
  }
}

Element::~Element() {

}

void Element::replaceTexture(const std::string &key, const std::string &texture) {
  for (auto &face : faces_) {
    face->replaceTexture(key, texture);
  }
}
}