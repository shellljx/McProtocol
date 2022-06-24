//
// Created by 李金祥 on 2022/6/19.
//

#pragma once
#include <string>

namespace McRenderer {
class AssetManager {
 public:
  AssetManager();
  ~AssetManager();

  static std::string getAssetDirPath();
  const unsigned char * getData();

 private:
  unsigned char* data = nullptr;
};
}

