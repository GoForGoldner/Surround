#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <vector>

#include "playerInfo.h"

typedef uint32_t enet_uint32;

class Model {
 public:
  Model(size_t arrSize);
  void updatePlayer(enet_uint32 id, int x, int y);
  const std::vector<std::vector<enet_uint32>>& getBoard();

 private:
  std::vector<std::vector<enet_uint32>> mArr;
};

#endif