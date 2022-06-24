//
// Created by 李金祥 on 2022/6/17.
//

#include "Face.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace McRenderer {
Face::Face(const float *matrix, const std::vector<float> textures) {
  for (int i = 0; i < 16; ++i) {
    modelMatrix_[i] = matrix[i];
  }

  for (int i = 0; i < 4; i++) {
    textureCoords_[i] = textures[i] * 0.03125;
  }
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

Face Face::Create(Point3D from, Point3D to, FaceInfo *info) {
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
  if (info->getOrientation() == Orientation::Top) {
    return Face(model_ptr, {27.4375, 6.375, 27.5625, 6.5});
  }
  return Face(model_ptr, {27.0002, 6.0002, 28 - 0.0002, 7 - 0.0002});
}
}