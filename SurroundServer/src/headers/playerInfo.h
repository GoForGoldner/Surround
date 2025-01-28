#pragma once
#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <SFML/System/Vector2.hpp>
#include <vector>

#include <enet/enet.h>
#include "player.h"

enum PlayerState { PLAYING, LOST };
enum Direction { UP, DOWN, LEFT, RIGHT };

class PlayerInfo {
 public:
  PlayerInfo(const enet_uint32 id, std::vector<std::vector<enet_uint32>>& arr);

  PlayerState PlayerInfo::updatePlayer(Direction direction, size_t arrSize,
                                       std::string& str);

  int getId() const;
  PlayerState getState() const;
  sf::Vector2i getNode() const;

 private:
  const enet_uint32 mId;
  PlayerState mPlayerState;
  sf::Vector2i mNode;
  std::vector<std::vector<enet_uint32>>& mArr;
};

#endif  // PLAYERINFO_H