#include "model.h"
#include <enet/enet.h>
#include <iostream>

Model::Model(size_t arrSize)
    : mArraySize(arrSize),
      mIdMap(std::unordered_map<int, std::unique_ptr<PlayerInfo>>()),
      mArr(std::vector<std::vector<enet_uint32>>(
          arrSize, std::vector<enet_uint32>(arrSize, -1))) {}

const std::vector<std::vector<enet_uint32>> Model::getBoard() const {
  return mArr;
}

void Model::addPlayer(const Player& player, enet_uint32 id) {
  std::cout << "MODEL: " << id << " added." << std::endl;

  // Add to the players list
  mActivePlayers.push_back({id, Direction::DOWN});
  // Add to the players map
  mIdMap[id] = std::make_unique<PlayerInfo>(PlayerInfo(id, mArr));
}

void eraseIdFromMActivePlayers(
    enet_uint32 id,
    std::vector<std::pair<enet_uint32, Direction>>& mActivePlayers) {
  for (auto it = mActivePlayers.begin(); it != mActivePlayers.end(); ++it) {
    if (it->first == id) {
      mActivePlayers.erase(it);
      break;
    }
  }
}

std::string Model::updatePlayer(enet_uint32 id, Direction direction) {
  std::string str;
  std::cout << "MODEL: " << id << " updated." << std::endl;
  if (mIdMap[id]->updatePlayer(direction, mArraySize, str) == PlayerState::LOST) {
    eraseIdFromMActivePlayers(id, mActivePlayers);
  }

  return str;
}

std::string Model::updatePlayers() {
  std::string str;
  for (auto pair : mActivePlayers) {
    str += updatePlayer(pair.first, pair.second);
  }

  return str;
}

void Model::changePlayerDirection(enet_uint32 id, Direction direction) {
  std::cout << "MODEL: " << id << " direction changed." << std::endl;
  for (auto it = mActivePlayers.begin(); it != mActivePlayers.end(); ++it) {
    if (it->first == id) {
      it->second = direction;
      break;
    }
  }
}

bool Model::GameOver() const { return mActivePlayers.empty(); }