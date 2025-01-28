#ifndef MODEL_HPP
#define MODEL_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

#include "playerInfo.cpp"

class Model {
 public:
  explicit Model(size_t arrSize);

  bool GameOver();

  int addPlayer(const Player& player);

  void UpdatePlayer(int id, Direction direction);

 private:
  const size_t mArraySize;
  std::unordered_map<int, std::unique_ptr<PlayerInfo>> mIdMap;
  int mNextId;
  std::vector<std::vector<int>> mArr;
  std::unordered_set<int> mActivePlayers;
};

#endif