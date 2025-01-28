#pragma once
#include "viewWindow.h"
#include "view.h"

class Menu : public ViewWindow {
 public:
  static void processEvents(const sf::Event& event, sf::RenderWindow& window,
                            View& view);
  static void display(sf::RenderWindow& window);
};