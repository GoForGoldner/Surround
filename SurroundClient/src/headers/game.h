#pragma once
#include "view.h"
#include "viewWindow.h"

#include <SFML/Graphics.hpp>
#include <playerInfo.h>
#include "enet/enet.h"

class Game : public ViewWindow {
 public:

  void processEvents(const sf::Event& event, sf::RenderWindow& window,
                     View& view, Controller& controller);

  void display(sf::RenderWindow& window);

  private:
  Direction m_currentDireciton;
};