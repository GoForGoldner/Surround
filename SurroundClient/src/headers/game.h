#pragma once
#include <playerInfo.h>

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

#include "viewWindow.h"

typedef uint32_t enet_uint32;

class View;        // Forward declaration
class Controller;  // Forward declaration

class Game : public ViewWindow {
 public:
  Game(int boardWidth, int boardHeight, int numberOfPlayers);

  virtual void processViewEvents(const sf::Event& event,
                                 sf::RenderWindow& window, View& view,
                                 Controller& controller) override;

  virtual void display(sf::RenderWindow& window) override;

  virtual void processServerEvents(const char* packet) override;

 private:
  Direction m_currentDireciton;

  std::unordered_map<enet_uint32, sf::Color> m_idToColor;
  std::vector<std::vector<enet_uint32>> m_board;
};