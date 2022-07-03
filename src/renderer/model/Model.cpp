//
// Created by 李金祥 on 2022/6/17.
//

#include "Model.h"
#include "renderer/AssetManager.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>

namespace McRenderer {
Model::Model() {

}

Model::~Model() {

}

void Model::ParseModelFromJson(Model *model, Type type, const char *name) {
  auto subDir = "block";
  if (type == ITEM) {
    subDir = "item";
  }
  auto modelPath = AssetManager::getAssetDirPath() + "/minecraft/models/" + subDir + "/" + +name + ".json";
  std::ifstream stream(modelPath);

  nlohmann::json modelJson = nlohmann::json::parse(stream);
  if (modelJson.contains("parent")) {
    auto parent = to_string(modelJson["parent"]);
    auto parentType = BLOCK;
    if (parent.find("minecraft:item") != std::string::npos) {
      parentType = ITEM;
    }
    auto nameStart = parent.find('/') + 1;
    auto parentName = parent.substr(nameStart, parent.length() - nameStart - 1);
    ParseModelFromJson(model, parentType, parentName.c_str());
  }

  if (modelJson.contains("elements")) {
    for (auto &json : modelJson.at("elements")) {
      model->elements_.push_back(std::make_unique<Element>(json));
    }
  }

  if (modelJson.contains("textures")) {
    for (const auto &item : modelJson.at("textures").items()) {
      const auto &key = item.key();
      auto value = item.value().get<std::string>();
      for (auto &element : model->elements_) {
        element->replaceTexture(key, value);
      }
    }
  }
}

std::unique_ptr<Model> Model::MakeBlockWithName(const char *name) {
  auto model = new Model();
  ParseModelFromJson(model, BLOCK, name);
  return std::unique_ptr<Model>(model);
}

std::unique_ptr<Model> Model::MakeItemWithName(const char *name) {
  auto model = new Model();
  ParseModelFromJson(model, ITEM, name);
  return std::unique_ptr<Model>(model);
}

std::vector<Face> Model::generateFaces() {
  std::vector<Face> faces;
  for (auto &element: elements_) {
    for (auto &info : element->getFaces()) {
      faces.push_back(Face::Create(element->getFrom(), element->getTo(), info.get()));
    }
  }
  return faces;
}
}