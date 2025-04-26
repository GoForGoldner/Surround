#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include <enet/enet.h>

#include "game.h"
#include "menu.h"
#include "waitingRoom.h"

class Controller;  // Forward declaration of Controller

class View {
 public:
  enum Mode { MENU, WAITING_ROOM, GAME };

  View(Menu& menu, WaitingRoom& waitingRoom, Game& game);
  
  void changeMode(Mode mode);
  void display();
  bool isOpen() const;
  void close();
  
  void processEvents(Controller& controller);
  

 private:
  std::unordered_map<enet_uint32, sf::Color> m_idToColor;
  sf::RenderWindow m_window;
  Mode m_currentMode;

  Menu& m_menu;
  WaitingRoom& m_waitingRoom;
  Game& m_game;
};
