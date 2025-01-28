#pragma once
#include <string>

class Player {
 public:
  Player(std::string name, size_t wins);

 private:
  std::string m_name;
  size_t m_wins;
};