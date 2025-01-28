#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "enet/enet.h"
#include <vector>

#include "playerInfo.h"

class Model {
 public:
  Model(size_t arrSize);
  void updatePlayer(enet_uint32 id, int x, int y);
  const std::vector<std::vector<enet_uint32>>& getBoard();

 private:
  std::vector<std::vector<enet_uint32>> mArr;
};

#endif