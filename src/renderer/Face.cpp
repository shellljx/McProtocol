//
// Created by 李金祥 on 2022/6/17.
//

#include "Face.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace McRenderer {
Face::Face(const Orientation orientation,const std::vector<float> textures) {
  glm::mat4 model = glm::mat4(1.0);

  switch (orientation) {
    case Orientation::Top:model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::East:
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::West:model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::North:model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case Orientation::South:model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      break;
  }
  const float *model_ptr = glm::value_ptr(model);

  for (int i = 0; i < 16; ++i) {
    modelMatrix_[i] = model_ptr[i];
  }

  for(int i = 0;i<4;i++){
    textureCoords_[i] = textures[i]*0.03125;
  }
}

Face::~Face() {

}

const std::vector<float> Face::botoom_face = {
    //x       y        z
    -0.9999f, -0.9999f, -0.9999f,
    0.9999f, -0.9999f, -0.9999f,
    -0.9999f, -0.9999f, 0.9999f,
    0.9999f, -0.9999f, 0.9999f
};
}