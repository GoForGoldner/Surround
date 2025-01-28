#include <gtest/gtest.h>

#include <vector>

#include "playerInfo.h"

class PlayerInfoTest : public testing::Test {
 protected:
  void SetUp() override {
    // Initialize a 5x5 grid with all zeros.
    grid = std::vector<std::vector<int>>(5, std::vector<int>(5, 0));
    player = new PlayerInfo(1, grid);
  }

  void TearDown() override { delete player; }

  std::vector<std::vector<int>> grid;
  PlayerInfo* player;
};

TEST_F(PlayerInfoTest, InitialState) {
  EXPECT_EQ(player->getId(), 1);
  EXPECT_EQ(player->getState(), PlayerState::PLAYING);
  EXPECT_EQ(player->getNode(), sf::Vector2i(0, 0));
}

TEST_F(PlayerInfoTest, MoveUpOutOfBounds) {
  PlayerState state = player->updatePlayer(Direction::UP, grid.size());
  EXPECT_EQ(state, PlayerState::LOST);
  EXPECT_EQ(player->getState(), PlayerState::LOST);
  EXPECT_EQ(grid[0][0], 1);  // The player's ID should be set in the current cell.
}

TEST_F(PlayerInfoTest, MoveDownWithinBounds) {
  PlayerState state = player->updatePlayer(Direction::DOWN, grid.size());
  EXPECT_EQ(state, PlayerState::PLAYING);
  EXPECT_EQ(player->getNode(), sf::Vector2i(0, 1));
}

TEST_F(PlayerInfoTest, MoveDownOutOfBounds) {
  // Move player to the bottom-most row
  for (int i = 0; i < 4; ++i) {
    player->updatePlayer(Direction::DOWN, grid.size());
  }
  PlayerState state = player->updatePlayer(Direction::DOWN, grid.size());
  EXPECT_EQ(state, PlayerState::LOST);
}

TEST_F(PlayerInfoTest, MoveLeftOutOfBounds) {
  PlayerState state = player->updatePlayer(Direction::LEFT, grid.size());
  EXPECT_EQ(state, PlayerState::LOST);
  EXPECT_EQ(grid[0][0], 1);  // The player's ID should be set in the current cell.
}

TEST_F(PlayerInfoTest, MoveRightWithinBounds) {
  PlayerState state = player->updatePlayer(Direction::RIGHT, grid.size());
  EXPECT_EQ(state, PlayerState::PLAYING);
  EXPECT_EQ(player->getNode(), sf::Vector2i(1, 0));
}

TEST_F(PlayerInfoTest, MoveRightOutOfBounds) {
  // Move player to the right-most column
  for (int i = 0; i < 4; ++i) {
    player->updatePlayer(Direction::RIGHT, grid.size());
  }
  PlayerState state = player->updatePlayer(Direction::RIGHT, grid.size());
  EXPECT_EQ(state, PlayerState::LOST);
}

TEST_F(PlayerInfoTest, UpdateGridOnMove) {
  player->updatePlayer(Direction::DOWN, grid.size());
  EXPECT_EQ(grid[0][0],
            1);  // The starting position should be marked with the player's ID.
  EXPECT_EQ(player->getNode(), sf::Vector2i(0, 1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}