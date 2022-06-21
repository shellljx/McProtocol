//
// Created by 李金祥 on 2022/6/18.
//
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Atlas.h"

namespace McRenderer {

unsigned char *pack2DTexture(const std::vector<std::string> &paths, bool save) {
  auto outData = new unsigned char[512 * 512 * 4];
  int imageIndex = 0;

  try {
    for (int i = 0; i < paths.size(); ++i) {
      int imageY = imageIndex / 32;
      int imageX = imageIndex % 32;
      int imageOffset = imageY * 16 * 512 * 4 + imageX * 16 * 4;
      if (paths[i].empty()) {
        continue;
      }
      int image_width, image_height, nrChannels;
      auto path = "/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets/minecraft/textures/block/"+paths[i];

      unsigned char *data = stbi_load(
          path.c_str(),
          &image_width,
          &image_height,
          &nrChannels,
          0);

      int readP = 0;
      for (int row = 0; row < 16; ++row) {
        int rowOffset = imageOffset + row * 512 * 4;
        for (int col = 0; col < 16; ++col) {
          int colOffset = rowOffset + col * 4;
          int r = 0;
          int g = 0;
          int b = 0;
          int a = 0;
          switch (nrChannels) {
            case 1:r = data[readP++];
              g = data[readP++];
              b = data[readP++];
              a = 255;
              break;
            case 2:r = data[readP++];
              g = data[readP++];
              b = data[readP++];
              a = data[readP++];
              break;
            case 3:r = data[readP++];
              g = data[readP++];
              b = data[readP++];
              a = 255;
              break;
            case 4:r = data[readP++];
              g = data[readP++];
              b = data[readP++];
              a = data[readP++];
              break;
          }
          outData[colOffset] = r;
          outData[colOffset + 1] = g;
          outData[colOffset + 2] = b;
          outData[colOffset + 3] = a;
        }
      }
      stbi_image_free(data);
      imageIndex++;
    }
  } catch (const std::runtime_error& e) {
   int i = 0;
   i++;
  }

  if (save) {
    stbi_write_png("/Users/lijinxiang/Desktop/test/test.png", 512, 512, 4, outData, 512 * 4);
  }
  return outData;
}
}