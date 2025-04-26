#pragma once
#include "viewWindow.h"

class View;        // Forward declaration
class Controller;  // Forward declaration

class WaitingRoom : public ViewWindow {
 public:
  WaitingRoom();

  virtual void processViewEvents(const sf::Event& event,
                                 sf::RenderWindow& window,
                         View& view, Controller& controller) override;

  virtual void display(sf::RenderWindow& window) override;

  virtual void processServerEvents(const char* packet) override;

 private:
  std::string m_waitingMessage;
};