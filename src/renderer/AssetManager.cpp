//
// Created by 李金祥 on 2022/6/19.
//

#include "AssetManager.h"
#include <vector>
#include "Atlas.h"
#include <dirent.h>

namespace McRenderer {
AssetManager::AssetManager() {

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

  data = pack2DTexture(paths, true);
}

AssetManager::~AssetManager() {
  delete[] data;
}

const unsigned char *AssetManager::getData() {
  return data;
}

std::string AssetManager::getAssetDirPath() {
  return "/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets";
}
}