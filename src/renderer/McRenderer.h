//
// Created by 李金祥 on 2022/6/4.
//

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/vec4.hpp"

namespace McRenderer{
class McRenderer {
 public:
  explicit McRenderer();
  ~McRenderer();

  int run();

 private:
  void processInput(GLFWwindow* window);
};
}
