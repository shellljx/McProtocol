//
// Created by 李金祥 on 2022/6/19.
//

#include "AssetManager.h"
#include <memory>
#include <vector>
#include "Atlas.h"
#include <dirent.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace McRenderer {
AssetManager::AssetManager() {
  atlas_ = std::make_unique<Atlas>();

  std::vector<std::string> paths;
  DIR *dr;
  struct dirent *en;
  dr =
      opendir("/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets/minecraft/textures/block"); //open all directory
  if (dr) {
    while ((en = readdir(dr)) != NULL) {
      std::string name = en->d_name;
      if (name.find(".png") == std::string::npos || name.find("mcmeta") != std::string::npos) {
        continue;
      }
      paths.emplace_back(en->d_name);
    }
    closedir(dr); //close all directory
  }

  atlas_->pack2DTexture(paths, true);

  //load block states
  auto blockspath = "/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets/minecraft/blocks.json";
  std::ifstream blockstream(blockspath);
  nlohmann::json statesJson = nlohmann::json::parse(blockstream);
  for(auto& state : statesJson.items()){
    auto key = state.key();
    auto value = state.value();

    auto name = key.substr(10, key.length());
    auto statepath = "/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets/minecraft/blockstates/"+name+".json";

    std::ifstream stateStream(statepath);
    nlohmann::json json = nlohmann::json::parse(stateStream);

  }
}

AssetManager::~AssetManager() {
}

AssetManager &AssetManager::getInstance() {
  static AssetManager instance;
  return instance;
}

std::string AssetManager::getAssetDirPath() {
  return "/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets";
}
}