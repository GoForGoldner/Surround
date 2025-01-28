#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "playerInfo.h"
#include <enet/enet.h>

class Model {
 public:
  explicit Model(size_t arrSize);

  const std::vector<std::vector<enet_uint32>> getBoard() const;

  void addPlayer(const Player& player, enet_uint32 id);

  std::string updatePlayer(enet_uint32 id, Direction direction);

  std::string updatePlayers();

  void changePlayerDirection(enet_uint32 id, Direction direction);

  bool GameOver() const;

 private:
  const size_t mArraySize;
  std::vector<std::vector<enet_uint32>> mArr;
  std::unordered_map<int, std::unique_ptr<PlayerInfo>> mIdMap;
  std::vector<std::pair<enet_uint32, Direction>> mActivePlayers;
};

#endif