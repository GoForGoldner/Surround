#include "model.h"

#include <enet/enet.h>

#include <iostream>

Model::Model(size_t arrSize)
    : mArraySize(arrSize),
      mIdMap(std::unordered_map<enet_uint32, std::unique_ptr<PlayerInfo>>()),
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
  for (auto it = mActivePlayers.begin(); it != mActivePlayers.end();) {
    if (it->first == id) {
      it = mActivePlayers.erase(it);
      std::cout << "Removed id " << std::to_string(id) << std::endl;
      break;
    } else {
      ++it;
    }
  }
}

std::string Model::updatePlayer(enet_uint32 id, Direction direction) {
  if (mIdMap.find(id) == mIdMap.end()) {
    std::cout << "Player with id: " + id << "  isn't added." << std::endl;
  }

  std::string str = "";
  std::cout << "MODEL: " << id << " updated. Direction: " << direction
            << std::endl;

  if (mIdMap[id]->updatePlayer(direction, str) == PlayerState::LOST) {
    eraseIdFromMActivePlayers(id, mActivePlayers);
  }

  std::cout << "str is now: " << str << std::endl;

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
      std::cout << "Changed direction for " << std::to_string(id) << " "
                << direction << std::endl;
      it->second = direction;
      return;
    }
  }
}

bool Model::GameOver() const { return mActivePlayers.empty(); }