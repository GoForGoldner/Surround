#include "controller.h"
#include "game.h"
#include "menu.h"
#include "model.h"
#include "view.h"

const int PLAYERS = 1;
const int BOARD_WIDTH = 32;
const int BOARD_HEIGHT = 32;

int main() {
  Menu menu;
  WaitingRoom waitingRoom;
  Game game(BOARD_WIDTH, BOARD_HEIGHT, PLAYERS);

  View view(menu, waitingRoom, game);

  Controller controller(view, menu, waitingRoom, game);
  controller.begin();
}