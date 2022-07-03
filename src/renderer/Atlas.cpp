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
#include "finders_interface.h"

namespace McRenderer {

Atlas::Atlas() {}
Atlas::~Atlas() {}

void Atlas::pack2DTexture(const std::vector<std::string> &paths, bool save) {
  using spaces_type = rectpack2D::empty_spaces<false, rectpack2D::default_empty_spaces>;
  using rect_type = rectpack2D::output_rect_t<spaces_type>;

  std::vector<rect_type> rectangles;
  std::map<std::string, std::unique_ptr<McProtocol::ByteData>> textureBytes;
  std::vector<Texture *> textures;

  for (int i = 0; i < paths.size(); ++i) {
    int image_width, image_height, nrChannels;
    auto path =
        "/Users/lijinxiang/CLionProjects/minecraft/socket/assets/1.18.2/assets/minecraft/textures/block/" + paths[i];
    unsigned char *data = stbi_load(
        path.c_str(),
        &image_width,
        &image_height,
        &nrChannels,
        0);
    auto name = "minecraft:block/"+paths[i].substr(0, paths[i].find(".png"));
    textureBytes[name] = McProtocol::ByteData::MakeCopy(data, image_width * image_height * nrChannels);
    textures.push_back(new Texture(name, image_width, image_height, nrChannels));
    rectangles.emplace_back(rectpack2D::rect_xywh(0, 0, image_width, image_height));
  }

  const auto result_size = rectpack2D::find_best_packing<spaces_type>(
      rectangles,
      make_finder_input(
          1024,
          -4,
          [](rect_type &) {
            return rectpack2D::callback_result::CONTINUE_PACKING;
          },
          [](rect_type &) {
            return rectpack2D::callback_result::ABORT_PACKING;
          },
          rectpack2D::flipping_option::DISABLED
      )
  );
  width_ = result_size.w;
  height_ = result_size.h;

  for (int i = 0; i < rectangles.size(); ++i) {
    textures[i]->setLocation({rectangles[i].x, rectangles[i].y});
  }

  auto outData = new unsigned char[result_size.w * result_size.h * 4];

  for (int i = 0; i < textures.size(); ++i) {
    auto texture = textures[i];
    int imageOffset = texture->getLocation().y * result_size.w * 4 + texture->getLocation().x * 4;

    auto data = textureBytes[texture->getName()]->data();

    int readP = 0;
    for (int row = 0; row < texture->getHeight(); ++row) {
      int rowOffset = imageOffset + row * result_size.w * 4;
      for (int col = 0; col < texture->getWidth(); ++col) {
        int colOffset = rowOffset + col * 4;
        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;
        switch (texture->getDepth()) {
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
    textureMap_[textures[i]->getName()] = std::shared_ptr<Texture>(textures[i]);
  }
  textures.clear();

  if (save) {
    stbi_write_png("/Users/lijinxiang/Desktop/test/test.png",
                   result_size.w,
                   result_size.h,
                   4,
                   outData,
                   result_size.w * 4);
  }
  datas_ = McProtocol::ByteData::MakeWithoutCopy(outData, result_size.w * result_size.h * 4);
}

std::shared_ptr<Texture> Atlas::getTexture(const std::string &name) {
  return textureMap_[name];
}
}