#pragma once
#include <SFML/Graphics.hpp>

class View;        // Forward declaration
class Controller;  // Forward declaration

class ViewWindow {
 public:
  virtual void processViewEvents(const sf::Event& event,
                                 sf::RenderWindow& window, View& view,
                                 Controller& controller) = 0;
  virtual void display(sf::RenderWindow& window) = 0;

  virtual void processServerEvents(const char* packet) = 0;
};