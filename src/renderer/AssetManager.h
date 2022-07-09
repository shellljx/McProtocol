//
// Created by 李金祥 on 2022/6/19.
//

#pragma once
#include "Atlas.h"
#include "BlockStates.h"

namespace McRenderer {
class AssetManager {
 public:
  AssetManager();
  ~AssetManager();

  static std::string getAssetDirPath();
  static AssetManager& getInstance();

  std::shared_ptr<Atlas> getAtlas(){
    return atlas_;
  }

 private:
  std::shared_ptr<Atlas> atlas_ = nullptr;
  std::map<int, std::shared_ptr<BlockStates>> block_states_;
};
}

