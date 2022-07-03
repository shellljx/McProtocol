//
// Created by 李金祥 on 2022/6/4.
//

#include "McRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ShaderLoader.h"
#include <stdlib.h>
#include "Face.h"
#include "Atlas.h"
#include "AssetManager.h"
#include "renderer/model/Model.h"

namespace McRenderer {

McRenderer::McRenderer() {

}

McRenderer::~McRenderer() {

}

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
GLfloat yaw =
    -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = 800 / 2.0;
GLfloat lastY = 600 / 2.0;
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
  lastX = xpos;
  lastY = ypos;

  GLfloat sensitivity = 0.05;    // Change this value to your liking
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(front);
}

void errorcallback(int error, const char *msg) {
  std::string s = msg;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
const std::vector<float> color_day({0.6f, 0.85f, 0.9f});
const std::vector<float> color_night({0.1f, 0.1f, 0.1f});

int McRenderer::run() {
  glfwSetErrorCallback(errorcallback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 500, "McRenderer", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  glEnable(GL_DEPTH_TEST);

  auto program = loadShader("vertex_shader.vs", "fragment_shader.fs");

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

  // world space positions of our cubes
  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
//      glm::vec3(0.0f, 2.0f, 0.0f),
//      glm::vec3(0.0f, 4.0f, 0.0f),
//      glm::vec3(0.0f, 6.0f, 0.0f),
//      glm::vec3(2.0f, 0.0f, 0.0f),
//      glm::vec3(2.0f, 2.0f, 0.0f),
//      glm::vec3(2.0f, 4.0f, 0.0f),
//      glm::vec3(2.0f, 6.0f, 0.0f),
//      glm::vec3(4.0f, 0.0f, 0.0f),
//      glm::vec3(4.0f, 2.0f, 0.0f),
//      glm::vec3(4.0f, 4.0f, 0.0f),
//      glm::vec3(4.0f, 6.0f, 0.0f),
//
//      glm::vec3(0.0f, 0.0f, -2.0f),
//      glm::vec3(0.0f, 2.0f, -2.0f),
//      glm::vec3(0.0f, 4.0f, -2.0f),
//      glm::vec3(0.0f, 6.0f, -2.0f),
//      glm::vec3(2.0f, 0.0f, -2.0f),
//      glm::vec3(2.0f, 2.0f, -2.0f),
//      glm::vec3(2.0f, 4.0f, -2.0f),
//      glm::vec3(2.0f, 6.0f, -2.0f),
//      glm::vec3(4.0f, 0.0f, -2.0f),
//      glm::vec3(4.0f, 2.0f, -2.0f),
//      glm::vec3(4.0f, 4.0f, -2.0f),
//      glm::vec3(4.0f, 6.0f, -2.0f)
  };

  auto model = Model::MakeBlockWithName("jungle_log");

  auto faces = model->generateFaces();

  GLuint vbo, dataVbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, Face::botoom_face.size() * sizeof(float), Face::botoom_face.data(), GL_STATIC_DRAW);

  //(x,y,z) for bottom face
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

  glGenBuffers(1, &dataVbo);
  glBindBuffer(GL_ARRAY_BUFFER, dataVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * faces.size(), faces.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void *) 0);
  glVertexAttribDivisor(1, 1);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void *) (4 * sizeof(float)));
  glVertexAttribDivisor(2, 1);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void *) (8 * sizeof(float)));
  glVertexAttribDivisor(3, 1);

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void *) (12 * sizeof(float)));
  //Specify that only one instance of this must be sent to one index
  glVertexAttribDivisor(4, 1);

  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void *) (16 * sizeof(float)));
  //Specify that only one instance of this must be sent to one index
  glVertexAttribDivisor(5, 1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLuint texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  auto atlas = AssetManager::getInstance().getAtlas();
  if (atlas->getDatas()) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas->getWidth(), atlas->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas->getDatas());
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    return -1;
  }

  glUseProgram(program);
  glUniform1i(glGetUniformLocation(program, "texture1"), 0);
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    const float current_day_time = 0.5;
    std::vector<float> current_color(3);
    glm::vec4 v3;
    for (int i = 0; i < 3; ++i) {
      current_color[i] = 2.0f * ((0.5f - std::abs(current_day_time - 0.5f)) * color_day[i]
          + (0.5f - std::min(std::abs(1.0f - current_day_time), current_day_time)) * color_night[i]);
    }
    glClearColor(current_color[0], current_color[1], current_color[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUseProgram(program);
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    //GLuint modelLoc = glGetUniformLocation(program, "model");
    GLuint viewLoc = glGetUniformLocation(program, "view");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, &projection[0][0]);
    glBindVertexArray(vao);
//    for (GLuint i = 0; i < 1; i++) {
//      glm::mat4 model = glm::mat4(1.0f);
//      model = glm::translate(model, cubePositions[i]);
//      //model = glm::rotate(model, 20.0f * i, glm::vec3(0.5f, 1.0f, 0.0f));
//      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//      glDrawArrays(GL_TRIANGLES, 0, 36);
//    }
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, faces.size());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  //============
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glfwTerminate();
}

void McRenderer::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  float cameraSpeed = static_cast<float>(0.1);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * cameraFront;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
}
}