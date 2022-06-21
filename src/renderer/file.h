//
// Created by 李金祥 on 2022/6/19.
//
#pragma once

namespace McRenderer {
enum class Orientation{
  None = -1,
  Bottom = 0, //y = -1
  North, //z = -1
  West, //x = -1
  East, //x = 1
  South, //z = 1
  Top //y = 1
};
}