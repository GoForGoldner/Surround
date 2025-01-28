#include "view.h"

#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

View::View(int numberOfPlayers)
    : m_window(sf::RenderWindow({1280u, 720u}, "CMake SFML Project")) {
  m_window.setFramerateLimit(144);
  // Set default colors for known IDs
  m_idToColor[-1] = sf::Color::Black;        // Example: Special Tile
  m_idToColor[0] = sf::Color::White;

  // Set default color for unknown IDs
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  for (int id = 0; id < numberOfPlayers; id++) {
    if (m_idToColor.find(id) == m_idToColor.end()) {
      // Generate random RGB values (0–255)
      sf::Uint8 r = static_cast<sf::Uint8>(std::rand() % 256);
      sf::Uint8 g = static_cast<sf::Uint8>(std::rand() % 256);
      sf::Uint8 b = static_cast<sf::Uint8>(std::rand() % 256);

      m_idToColor[id] = sf::Color(r, g, b);
    }
  }
}

void View::processEvents(std::function<void(const sf::Event&)> eventHandler) {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    }
    eventHandler(event);  // Forward events to Controller
  }
}

bool View::isOpen() const { return m_window.isOpen(); }

void View::displayBoard(const std::vector<std::vector<int>>& board) {
  if (board.empty()) return;

  m_window.clear();  // Clear the previous frame

  int rectWidth = m_window.getSize().x / board[0].size();
  int rectHeight = m_window.getSize().y / board.size();

  for (int row = 0; row < board.size(); ++row) {
    for (int col = 0; col < board[row].size(); ++col) {
      sf::RectangleShape rect(sf::Vector2f(rectWidth, rectHeight));
      rect.setPosition(sf::Vector2f(rectWidth * col, rectHeight * row));

      rect.setFillColor(m_idToColor[board[row][col]]);

      m_window.draw(rect);
    }
  }


  m_window.display();
}
