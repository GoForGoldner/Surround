#include "playerInfo.h"

#include <iostream>
#include <random>  // For random number generation

PlayerInfo::PlayerInfo(const enet_uint32 id,
                       std::vector<std::vector<enet_uint32>>& arr)
    : mId(id),
      mPlayerState(PlayerState::PLAYING),
      mNode(sf::Vector2i(0, 0)),
      m_arrSize(arr.size()),
      mArr(arr) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> disX(0, mArr[0].size() - 1);
  std::uniform_int_distribution<> disY(0, mArr.size() - 1);

  // Generate random coordinates
  int randomY, randomX;
  do {
    randomY = disX(gen);
    randomX = disY(gen);
  } while (mArr[randomY][randomX] != -1);

  mNode = sf::Vector2i(randomX, randomY);
}

PlayerState PlayerInfo::updatePlayer(Direction direction, std::string& str) {
  std::string s = std::to_string(mId) + " " + std::to_string(mNode.x);
  s += " " + std::to_string(mNode.y) + "\n";
  
  std::cout << s << std::endl;
  str = s;

  mArr[mNode.y][mNode.x] = mId;

  switch (direction) {
    case UP:
      if (mNode.y - 1 < 0 || mArr[mNode.y - 1][mNode.x] != -1) {
        mPlayerState = PlayerState::LOST;
      } else {
        --mNode.y;
      }
      break;
    case DOWN:
      if (mNode.y + 1 >= m_arrSize || mArr[mNode.y + 1][mNode.x] != -1) {
        mPlayerState = PlayerState::LOST;
      } else {
        ++mNode.y;
      }
      break;
    case LEFT:
      if (mNode.x - 1 < 0 || mArr[mNode.y][mNode.x - 1] != -1) {
        mPlayerState = PlayerState::LOST;
      } else {
        --mNode.x;
      }
      break;
    case RIGHT:
      if (mNode.x + 1 >= m_arrSize || mArr[mNode.y][mNode.x + 1] != -1) {
        mPlayerState = PlayerState::LOST;
      } else {
        ++mNode.x;
      }
      break;
    default:
      break;
  }

  std::cout << "head is now (" << mNode.x << ", " << mNode.y << ")"
            << std::endl;

  mArr[mNode.y][mNode.x] = 0;
  return mPlayerState;
}

int PlayerInfo::getId() const { return mId; }

PlayerState PlayerInfo::getState() const { return mPlayerState; }

sf::Vector2i PlayerInfo::getNode() const { return mNode; }
