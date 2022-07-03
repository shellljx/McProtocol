//
// Created by 李金祥 on 2022/6/17.
//

#include "Face.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "AssetManager.h"

namespace McRenderer {
Face::Face(const float *matrix, const FaceInfo *info) {
  for (int i = 0; i < 16; ++i) {
    modelMatrix_[i] = matrix[i];
  }

  auto atlas = AssetManager::getInstance().getAtlas();
  auto texture = atlas->getTexture(info->getTexture());
  auto u1 = (texture->getLocation().x + info->getUvStart().x) / atlas->getWidth() + 0.0002;
  auto v1 = (texture->getLocation().y + info->getUvStart().y) / atlas->getHeight() + 0.0002;

  auto u2 = (texture->getLocation().x + info->getUvEnd().x) / atlas->getWidth() - 0.0002;
  auto v2 = (texture->getLocation().y + info->getUvEnd().y) / atlas->getHeight() - 0.0002;

  textureCoords_[0] = u1;
  textureCoords_[1] = v1;
  textureCoords_[2] = u2;
  textureCoords_[3] = v2;
}

Face::~Face() {

}

const std::vector<float> Face::botoom_face = {
    //x       y        z
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

Face Face::Create(Point3D from, Point3D to, const FaceInfo *info) {
  glm::mat4 model = glm::mat4(1.0);

  model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
  if (to.y < 16) {
    model = glm::translate(model, glm::vec3(0.0f, (to.y - 16) / 16.f, 0.0f));
  }
  model = glm::scale(model, glm::vec3(abs(to.x - from.x) / 16.f, abs(to.y - from.y) / 16.f, abs(to.z - from.z) / 16.f));

  switch (info->getOrientation()) {
    case Orientation::Top:model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::East:model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::West:model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::North:model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::South:model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    case Orientation::Bottom:break;
    case Orientation::None:break;
  }
  const float *model_ptr = glm::value_ptr(model);
  return Face(model_ptr, info);
}
}