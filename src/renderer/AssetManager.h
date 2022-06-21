//
// Created by 李金祥 on 2022/6/19.
//

#pragma once

namespace McRenderer {
class AssetManager {
 public:
  AssetManager();
  ~AssetManager();

  const unsigned char * getData();
 private:
  unsigned char* data = nullptr;
};
}

