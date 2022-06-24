//
// Created by 李金祥 on 2022/6/17.
//

#pragma once
#include "Element.h"
#include "renderer/Face.h"

namespace McRenderer {
class Model {

  enum Type {
    BLOCK = 0,
    ITEM
  };

 public:
  explicit Model();
  ~Model();

  static std::unique_ptr<Model> MakeBlockWithName(const char *name);
  static std::unique_ptr<Model> MakeItemWithName(const char *name);

  std::vector<Face> generateFaces();

 private:
  static void ParseModelFromJson(Model *model, Type type, const char *name);

 private:
  std::vector<std::unique_ptr<Element>> elements_;
};
}
