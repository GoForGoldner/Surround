#pragma once
#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "player.h"

enum PlayerState { PLAYING, LOST };
enum Direction { UP, DOWN, LEFT, RIGHT };

class PlayerInfo {
 public:
  PlayerInfo(const int id, std::vector<std::vector<int>>& arr);

  PlayerState updatePlayer(Direction direction, size_t arrSize);

  int getId() const;
  PlayerState getState() const;
  sf::Vector2i getNode() const;

 private:
  const int mId;
  PlayerState mPlayerState;
  sf::Vector2i mNode;
  std::vector<std::vector<int>>& mArr;
};

#endif  // PLAYERINFO_H