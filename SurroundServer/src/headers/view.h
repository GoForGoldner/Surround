#pragma once
#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <functional>

class View {
 public:
  View(int numberOfPlayers);
  void processEvents(std::function<void(const sf::Event&)> eventHandler);
  bool isOpen() const;

  void displayBoard(const std::vector<std::vector<int>>& board);
  

 private:
  std::unordered_map<int, sf::Color> m_idToColor;
  sf::Vector2u m_windowSize;
  sf::RenderWindow m_window;
};

#endif  // Ends VIEW_H