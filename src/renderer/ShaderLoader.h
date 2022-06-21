//
// Created by 李金祥 on 2022/6/4.
//

#ifndef SOCKET_SRC_RENDERER_SHADERLOADER_H_
#define SOCKET_SRC_RENDERER_SHADERLOADER_H_
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "OpenGL/gltypes.h"
#include "OpenGL/gl3.h"

static std::string readFile(const char * path) {
  std::string content;
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    std::string name("/Users/lijinxiang/CLionProjects/minecraft/socket/assets");
    name.append("/shader/");
    name.append(path);
    fileStream.open(name);
    std::stringstream shaderStream;
    shaderStream << fileStream.rdbuf();
    fileStream.close();
    content = shaderStream.str();
  } catch (std::ifstream::failure &e) {
    std::cout << "read file error " << e.what() << std::endl;
  }
  return content;
}

static void checkCompileError(GLuint shader, std::string type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::cout << "shader compile error " << type << " info " << infoLog << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      std::cout << "program linking error " << type << infoLog << std::endl;
    }
  }
}

static GLuint loadShader(const char * vertexPath, const char* fragPath) {
  auto vShaderStr = readFile(vertexPath);
  auto fShaderStr = readFile(fragPath);
  const char* vShaderCode = vShaderStr.c_str();
  const char* fShaderCode = fShaderStr.c_str();

  GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShaderId, 1, &vShaderCode, nullptr);
  glCompileShader(vShaderId);
  checkCompileError(vShaderId, "VERTEX");
  GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShaderId, 1, &fShaderCode, nullptr);
  glCompileShader(fShaderId);
  checkCompileError(fShaderId, "FRAGMENT");

  GLuint program = glCreateProgram();
  glAttachShader(program, vShaderId);
  glAttachShader(program, fShaderId);
  glLinkProgram(program);
  checkCompileError(program, "PROGRAM");
  glDeleteShader(vShaderId);
  glDeleteShader(fShaderId);
  return program;
}
#endif //SOCKET_SRC_RENDERER_SHADERLOADER_H_
