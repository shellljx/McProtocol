//
// Created by 李金祥 on 2022/6/19.
//
#pragma once
#include <string>

namespace McRenderer {
enum class Orientation {
  None = -1,
  Bottom = 0, //y = -1
  North, //z = -1
  West, //x = -1
  East, //x = 1
  South, //z = 1
  Top //y = 1
};

typedef struct PointF {
  float x;
  float y;
} PointF;

typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Point3DF {
  float x;
  float y;
  float z;
} Point3DF;

typedef struct Point3D {
  int x;
  int y;
  int z;
} Point3D;

typedef struct Rect {
  float x;
  float y;
  float w;
  float h;
} Rect;

static Orientation GetOrientation(const char *orientation) {
  if (!strcmp(orientation, "south")) {
    return Orientation::South;
  } else if (!strcmp(orientation, "north")) {
    return Orientation::North;
  } else if (!strcmp(orientation, "east")) {
    return Orientation::East;
  } else if (!strcmp(orientation, "west")) {
    return Orientation::West;
  } else if (!strcmp(orientation, "up")) {
    return Orientation::Top;
  } else if (!strcmp(orientation, "down")) {
    return Orientation::Bottom;
  }
  return Orientation::None;
}
}