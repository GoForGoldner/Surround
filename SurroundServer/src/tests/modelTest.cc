//#include <gtest/gtest.h>
//
//#include "model.h"
//#include "player.h"
//
//class ModelTest : public testing::Test {
// protected:
//  void SetUp() override {
//    playerOneId = 0;
//    model.addPlayer(Player("Tyler", 0), 0);
//    playerTwoId = 1;
//    model.addPlayer(Player("Alex", 1), 1);
//    playerThreeId = 2;
//    model.addPlayer(Player("Mia", 2), 2);
//    playerFourId = 3;
//    model.addPlayer(Player("Jeff", 3), 3);
//  }
//
//  void TearDown() override {}
//
//  Model model = Model(10);
//  int playerOneId;
//  int playerTwoId;
//  int playerThreeId;
//  int playerFourId;
//};
//
//TEST_F(ModelTest, ValidAddPlayerIds) {
//  EXPECT_EQ(playerOneId, 0);
//  EXPECT_EQ(playerTwoId, 1);
//  EXPECT_EQ(playerThreeId, 2);
//  EXPECT_EQ(playerFourId, 3);
//}
//
//TEST_F(ModelTest, UpdatePlayer) {
//  EXPECT_EQ(playerOneId, 0);
//  EXPECT_EQ(model.UpdatePlayer(playerTwoId, Direction::DOWN),
//            PlayerState::PLAYING);
//
//  while (model.UpdatePlayer(playerTwoId, Direction::DOWN) ==
//         PlayerState::PLAYING) {
//    // Simulate moves until the player loses
//  }
//
//  EXPECT_EQ(model.UpdatePlayer(playerTwoId, Direction::DOWN),
//            PlayerState::LOST);
//}
//
//TEST_F(ModelTest, UpdateInvalidPlayer) {
//  int invalidPlayerId = 999;  // Assume this ID does not exist
//  EXPECT_EQ(model.UpdatePlayer(invalidPlayerId, Direction::UP),
//            PlayerState::LOST);
//}
//
//TEST_F(ModelTest, GameOver) {
//  EXPECT_FALSE(model.GameOver());
//
//  // Eliminate all players to trigger GameOver
//  while (model.UpdatePlayer(playerOneId, Direction::UP) ==
//         PlayerState::PLAYING) {
//  }
//  while (model.UpdatePlayer(playerTwoId, Direction::DOWN) ==
//         PlayerState::PLAYING) {
//  }
//  while (model.UpdatePlayer(playerThreeId, Direction::LEFT) ==
//         PlayerState::PLAYING) {
//  }
//  while (model.UpdatePlayer(playerFourId, Direction::RIGHT) ==
//         PlayerState::PLAYING) {
//  }
//
//  EXPECT_TRUE(model.GameOver());
//}
