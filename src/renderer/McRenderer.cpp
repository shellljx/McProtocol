//
// Created by 李金祥 on 2022/6/4.
//

#include "McRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ShaderLoader.h"
#include <stdlib.h>
#include "Atlas.h"
#include "AssetManager.h"
#include "renderer/model/Model.h"

namespace McRenderer {

McRenderer::McRenderer() {

}

McRenderer::~McRenderer() {

}

glm::vec3 cameraPos = glm::vec3(-154.0f, 100.0f, -81.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLuint vbo, dataVbo, vao;

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
std::atomic<bool> load = false;
int count = 0;
std::unique_ptr<Model> createModel(int id){
  switch (id) {
    case 9916:
      return nullptr;
    case 0:
      return nullptr;
    case 1:
      return Model::MakeBlockWithName("stone");
    case 2:
      return Model::MakeBlockWithName("granite");
    case 4:
      return Model::MakeBlockWithName("diorite");
    case 6:
      return Model::MakeBlockWithName("andesite");
    case 7:
      return Model::MakeBlockWithName("polished_andesite");
    case 8:
      return Model::MakeBlockWithName("grass_block");
    case 9:
      return Model::MakeBlockWithName("grass_block");
    case 10:
      return Model::MakeBlockWithName("dirt");
    case 14:
      return Model::MakeBlockWithName("cobblestone");
    case 15:
      return Model::MakeBlockWithName("oak_planks");
    case 16:
      return Model::MakeBlockWithName("spruce_planks");
    case 33:
      return Model::MakeBlockWithName("bedrock");
    case 34:
      //water
      return Model::MakeBlockWithName("water");
    case 35:
      return Model::MakeBlockWithName("water");
    case 36:
      return Model::MakeBlockWithName("water");
    case 37:
      return Model::MakeBlockWithName("water");
    case 38:
      return Model::MakeBlockWithName("water");
    case 39:
      return Model::MakeBlockWithName("water");
    case 40:
      return Model::MakeBlockWithName("water");
    case 41:
      return Model::MakeBlockWithName("water");
    case 42:
      return Model::MakeBlockWithName("water");
    case 50:
      return Model::MakeBlockWithName("lava");
    case 52:
      return Model::MakeBlockWithName("lava");
    case 54:
      return Model::MakeBlockWithName("lava");
    case 56:
      return Model::MakeBlockWithName("lava");
    case 66:
      return Model::MakeBlockWithName("sand");
    case 69:
      return Model::MakeBlockWithName("gold_ore");
    case 58:
      return Model::MakeBlockWithName("lava");
    case 71:
      return Model::MakeBlockWithName("iron_ore");
    case 73:
      return Model::MakeBlockWithName("coal_ore");
    case 77:
      return Model::MakeBlockWithName("oak_log");
    case 89:
      return Model::MakeBlockWithName("acacia_log");
    case 113:
      return Model::MakeBlockWithName("oak_wood");
    case 136:
      return Model::MakeBlockWithName("stripped_birch_wood");
    case 140:
      return Model::MakeBlockWithName("stripped_jungle_wood");
    case 149:
      return Model::MakeBlockWithName("oak_leaves");
    case 151:
      return Model::MakeBlockWithName("oak_leaves");
    case 153:
      return Model::MakeBlockWithName("oak_leaves");
    case 155:
      return Model::MakeBlockWithName("oak_leaves");
    case 200:
      return Model::MakeBlockWithName("jungle_leaves");
    case 205:
      return Model::MakeBlockWithName("acacia_leaves");
    case 207:
      return Model::MakeBlockWithName("acacia_leaves");
    case 209:
      return Model::MakeBlockWithName("acacia_leaves");
    case 263:
      return Model::MakeBlockWithName("lapis_ore");
    case 264:
      return Model::MakeBlockWithName("deepslate_lapis_ore");
    case 18684:
      return Model::MakeBlockWithName("deepslate");
    case 17714:
      return Model::MakeBlockWithName("tuff");
    case 3411:
      return Model::MakeBlockWithName("deepslate_diamond_ore");
    case 3955:
      return Model::MakeBlockWithName("deepslate_redstone_ore");
    case 70:
      return Model::MakeBlockWithName("deepslate_gold_ore");
    case 68:
      return Model::MakeBlockWithName("gravel");
    case 72:
      return Model::MakeBlockWithName("deepslate_iron_ore");
    case 128:
      return Model::MakeBlockWithName("dark_oak_wood");
    case 211:
      return Model::MakeBlockWithName("acacia_leaves");
    case 213:
      return Model::MakeBlockWithName("acacia_leaves");
    case 214:
      return Model::MakeBlockWithName("acacia_leaves");
    case 256:
      return Model::MakeBlockWithName("flowering_azalea_leaves");
    case 272:
      return Model::MakeBlockWithName("dispenser");
    case 273:
      return Model::MakeBlockWithName("dispenser");
    case 281:
      return Model::MakeBlockWithName("note_block");
    case 420:
      return Model::MakeBlockWithName("note_block");
    case 512:
      return Model::MakeBlockWithName("note_block");
    case 513:
      return Model::MakeBlockWithName("note_block");
    case 516:
      return Model::MakeBlockWithName("note_block");
    case 544:
      return Model::MakeBlockWithName("note_block");
    case 546:
      return Model::MakeBlockWithName("note_block");
    case 721:
      return Model::MakeBlockWithName("note_block");
    case 802:
      return Model::MakeBlockWithName("note_block");
    case 804:
      return Model::MakeBlockWithName("note_block");
    case 826:
      return Model::MakeBlockWithName("note_block");
    case 977:
      return Model::MakeBlockWithName("note_block");
    case 1022:
      return Model::MakeBlockWithName("note_block");
    case 1028:
      return Model::MakeBlockWithName("note_block");
    case 1030:
      return Model::MakeBlockWithName("note_block");
    case 1397:
      return Model::MakeBlockWithName("cobweb");
    case 1398:
      return Model::MakeBlockWithName("grass");
    case 1401:
      return Model::MakeBlockWithName("seagrass");
    case 1402:
      return Model::MakeBlockWithName("seagrass");
    case 1403:
      return Model::MakeBlockWithName("seagrass");
    case 1468:
      return Model::MakeBlockWithName("dandelion");
    case 1469:
      return Model::MakeBlockWithName("poppy");
    case 1472:
      return Model::MakeBlockWithName("azure_bluet");
    case 1478:
      return Model::MakeBlockWithName("cornflower");
    case 1617:
      return Model::MakeBlockWithName("fire_up0");
    case 1672:
      return Model::MakeBlockWithName("fire_up0");
    case 1860:
      return Model::MakeBlockWithName("fire_up0");
    case 1092:
      return Model::MakeBlockWithName("bed");
    case 1290:
      return Model::MakeBlockWithName("bed");
    case 1307:
      return Model::MakeBlockWithName("bed");
    case 1380:
      return Model::MakeBlockWithName("detector_rail");
    case 1493:
      return Model::MakeBlockWithName("wall_torch");
    case 1696:
      return Model::MakeBlockWithName("fire_up0");
    case 1993:
      return Model::MakeBlockWithName("fire_up0");
    case 1996:
      return Model::MakeBlockWithName("fire_up0");
    case 2044:
      return Model::MakeBlockWithName("oak_stairs");
    case 3410:
      return Model::MakeBlockWithName("diamond_ore");
    case 3705:
      return Model::MakeBlockWithName("rail");
    case 3953:
      return Model::MakeBlockWithName("redstone_ore");
    case 4016:
      return Model::MakeBlockWithName("clay");
    case 4050:
      return Model::MakeBlockWithName("oak_fence_gate");
    case 4058:
      return Model::MakeBlockWithName("oak_fence_gate");
    case 4062:
      return Model::MakeBlockWithName("oak_fence_gate");
    case 4065:
      return Model::MakeBlockWithName("oak_fence_gate");
    case 4066:
      return Model::MakeBlockWithName("oak_fence_gate");
    case 4938:
      return Model::MakeBlockWithName("glow_lichen");
    case 4988:
      return Model::MakeBlockWithName("glow_lichen");
    case 5004:
      return Model::MakeBlockWithName("glow_lichen");
    case 5010:
      return Model::MakeBlockWithName("glow_lichen");
    case 5012:
      return Model::MakeBlockWithName("glow_lichen");
    case 5015:
      return Model::MakeBlockWithName("glow_lichen");
    case 5016:
      return Model::MakeBlockWithName("glow_lichen");
    case 5017:
      return Model::MakeBlockWithName("glow_lichen");
    case 5019:
      return Model::MakeBlockWithName("glow_lichen");
    case 8143:
      return Model::MakeBlockWithName("tall_grass_bottom");
    case 8144:
      return Model::MakeBlockWithName("tall_grass_bottom");
    case 17818:
      return Model::MakeBlockWithName("copper_ore");
    case 17819:
      return Model::MakeBlockWithName("deepslate_copper_ore");
    default:
      int i=0;
      return Model::MakeBlockWithName("bedrock");
  }
}
void McRenderer::setData(const McProtocol::ServerChunkDataPacket *packet,int cx, int cz) {
  if (count>=4){
    return;
  }
  count++;
  auto chunkData = packet->getChunkData();
  for (int sectionY = 0; sectionY < 256 / 16; ++sectionY) {
    short blockCount = chunkData.readInt16();
    unsigned char bits_per_block = chunkData.readUint8();
    auto palette_type = (bits_per_block == 0? 0: (bits_per_block <=8?1:2));
    auto palette_length = 0;
    auto palette_value = 0;
    std::vector<int> palette;
    switch (palette_type) {
      case 0:
        palette_value = chunkData.readVarInt();
        break;
      case 1:
        if (bits_per_block < 4){
          bits_per_block = 4;
        }
        palette_length = chunkData.readVarInt();
        palette = std::vector<int>(palette_length);
        for (int p = 0; p < palette_length; ++p) {
          palette[p] = chunkData.readVarInt();
        }
        break;
      case 2:
        break;
    }
    unsigned int individual_value_mask = (unsigned int )((1<<bits_per_block) - 1);
    int data_array_size = chunkData.readVarInt();
    std::vector<unsigned long long int> data_array(data_array_size);
    for (int d = 0; d < data_array_size; ++d) {
      data_array[d] = chunkData.readUint64();
    }

    int bit_offset = 0;
    if (blockCount!=0){
      Point3D position;

      for (int y = 0; y < 16; ++y) {
        position.y = y+sectionY*16;
        for (int z = 0; z < 16; ++z) {
          position.z = z+cz*16;
          for (int x = 0; x < 16; ++x) {
            position.x = x+cx*16;
            if (palette_type == 0){
              //single
              auto model = createModel(palette_value);
              auto v = model->generateFaces(position);
              faces_.insert(faces_.end(), v.begin(), v.end());
              continue;
            }

            if (64-(bit_offset%64)<bits_per_block){
              bit_offset+=64-(bit_offset%64);
            }
            int start_long_index = bit_offset / 64;
            int end_long_index = start_long_index;
            int start_offset = bit_offset % 64;
            bit_offset += bits_per_block;
            unsigned int raw_id;
            if (start_long_index == end_long_index)
            {
              raw_id = (unsigned int)(data_array[start_long_index] >> start_offset);
            }
            else
            {
              int end_offset = 64 - start_offset;
              raw_id = (unsigned int)(data_array[start_long_index] >> start_offset | data_array[end_long_index] << end_offset);
            }
            raw_id &= individual_value_mask;

            if (palette_type == 1)
            {
              raw_id = palette[raw_id];
            }

            auto model = createModel(raw_id);
            if (model != nullptr){
              std::cout<<std::to_string(position.x)+","+std::to_string(position.y)+","+std::to_string(position.z)+": "+std::to_string(raw_id)<<std::endl;
              auto v = model->generateFaces(position);
              faces_.insert(faces_.end(), v.begin(), v.end());
            }
          }
        }
      }
    }

    unsigned char bits_per_biome = chunkData.readUint8();
    palette_type = (bits_per_biome == 0?0:(bits_per_biome<=3?1:2));
    switch (palette_type) {
      case 0:
        palette_value = chunkData.readVarInt();
        break;
      case 1:
        palette_length = chunkData.readVarInt();
        palette = std::vector<int>(palette_length);
        for (int j = 0; j <palette_length; ++j) {
          palette[j] = chunkData.readVarInt();
        }
        break;
      case 2:
        break;
    }
    individual_value_mask = (unsigned int)((1<<bits_per_biome) - 1);
    data_array_size = chunkData.readVarInt();
    data_array = std::vector<unsigned long long int>(data_array_size);
    for (int j = 0; j < data_array_size; ++j) {
      data_array[j] = chunkData.readUint64();
    }

    bit_offset = 0;
    for (int y = 0; y < 16 / 4; ++y) {
      for (int z = 0; z < 16 / 4; ++z) {
        for (int x = 0; x < 16 / 4; ++x) {
          const int biome_index = sectionY*64+y*16+z*4+x;
          if (palette_type == 0){
            continue;
          }
          if (64 - (bit_offset % 64) < bits_per_biome)
          {
            bit_offset += 64 - (bit_offset % 64);
          }
          int start_long_index = bit_offset / 64;
          int end_long_index = start_long_index;
          int start_offset = bit_offset % 64;
          bit_offset += bits_per_biome;

          unsigned int raw_id;
          if (start_long_index == end_long_index)
          {
            raw_id = (unsigned int)(data_array[start_long_index] >> start_offset);
          }
          else
          {
            int end_offset = 64 - start_offset;
            raw_id = (unsigned int)(data_array[start_long_index] >> start_offset | data_array[end_long_index] << end_offset);
          }
          raw_id &= individual_value_mask;
          if (palette_type == 1){
            raw_id = palette[raw_id];
          }
        }
      }
    }
  }
  load = true;
}

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

  auto model = Model::MakeBlockWithName("red_mushroom_block_inventory");
  std::vector<Face> faces;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      auto v = model->generateFaces(Point3D{i, 0, j});
      faces.insert(faces.end(), v.begin(), v.end());
    }
  }

  glGenBuffers(1, &dataVbo);
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
  glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * faces_.size(), faces_.data(), GL_STATIC_DRAW);

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
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 atlas->getWidth(),
                 atlas->getHeight(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 atlas->getDatas());
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    return -1;
  }

  glUseProgram(program);
  glUniform1i(glGetUniformLocation(program, "texture1"), 0);
  while (!glfwWindowShouldClose(window)) {
    if (load){
      load = false;

      glBindBuffer(GL_ARRAY_BUFFER, dataVbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * faces_.size(), faces_.data(), GL_STATIC_DRAW);
    }
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
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, faces_.size());
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
  float cameraSpeed = static_cast<float>(0.3);
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