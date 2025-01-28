#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include <enet/enet.h>

class Controller;  // Forward declaration of Controller

class View {
 public:
  enum Mode { MENU, WAITING_ROOM, GAME };

  View(int numberOfPlayers);
  void displayBoard(const std::vector<std::vector<enet_uint32>>& board);
  bool isOpen() const;
  void processEvents(Controller& controller);
  void changeMode(Mode mode);
  void display(const char* waitingMessage);
  void close();

 private:
  std::unordered_map<enet_uint32, sf::Color> m_idToColor;
  sf::Vector2u m_windowSize;
  sf::RenderWindow m_window;
  Mode m_currentMode;
};
