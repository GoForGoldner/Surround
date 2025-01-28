#include "model.h"

Model::Model(size_t arrSize)
    : mArr(std::vector<std::vector<enet_uint32>>(
          arrSize, std::vector<enet_uint32>(arrSize, -1))) {}

void Model::updatePlayer(enet_uint32 id, int x, int y) { mArr[y][x] = id; }

const std::vector<std::vector<enet_uint32>>& Model::getBoard() { return mArr; }