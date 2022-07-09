//
// Created by 李金祥 on 2022/6/4.
//

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/vec4.hpp"
#include "protocol/ingame/clientbound/chunk/ServerChunkDataPacket.h"
#include "Face.h"

namespace McRenderer{
class McRenderer {
 public:
  explicit McRenderer();
  ~McRenderer();

  int run();
  void setData(const McProtocol::ServerChunkDataPacket* packet, int x, int z);

 private:
  void processInput(GLFWwindow* window);

 private:
  std::vector<Face> faces_;
};
}
