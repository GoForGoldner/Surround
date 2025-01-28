#pragma once
#include <SFML/Graphics.hpp>
#include "view.h"

class ViewWindow {
  virtual void processEvents(const sf::Event& event, sf::RenderWindow& window,
                        View& view) = 0;
  virtual void display(sf::RenderWindow& window) = 0;
};