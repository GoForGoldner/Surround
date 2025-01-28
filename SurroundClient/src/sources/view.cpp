#include "view.h"

#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
#include "controller.h"
#include "game.h"
#include "menu.h"
#include "waitingRoom.h"
#include <iostream>

View::View(int numberOfPlayers)
    : m_window(sf::RenderWindow({1280u, 720u}, "CMake SFML Project")), m_currentMode(Mode::MENU) {
  m_window.setFramerateLimit(144);
  // Set default colors for known IDs
  m_idToColor[-1] = sf::Color::Black;  // Example: Special Tile
  m_idToColor[0] = sf::Color::White;

  // Set default color for unknown IDs
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void View::displayBoard(const std::vector<std::vector<enet_uint32>>& board) {
  if (board.empty() || m_currentMode != Mode::GAME) return;

  m_window.clear();  // Clear the previous frame

  int rectWidth = m_window.getSize().x / board[0].size();
  int rectHeight = m_window.getSize().y / board.size();

  for (int row = 0; row < board.size(); ++row) {
    for (int col = 0; col < board[row].size(); ++col) {
      if (m_idToColor.find(board[row][col]) == m_idToColor.end()) {
        // Generate random RGB values (0–255)
        sf::Uint8 r = static_cast<sf::Uint8>(std::rand() % 256);
        sf::Uint8 g = static_cast<sf::Uint8>(std::rand() % 256);
        sf::Uint8 b = static_cast<sf::Uint8>(std::rand() % 256);

        m_idToColor[board[row][col]] = sf::Color(r, g, b);
      }

      sf::RectangleShape rect(sf::Vector2f(rectWidth, rectHeight));
      rect.setPosition(sf::Vector2f(rectWidth * col, rectHeight * row));

      rect.setFillColor(m_idToColor[board[row][col]]);

      m_window.draw(rect);
    }
  }

  m_window.display();
}

void View::changeMode(Mode mode) { m_currentMode = mode; }

void View::processEvents(Controller& controller) {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    }
    
    switch (m_currentMode) {
      case MENU:
        Menu::processEvents(event, m_window, *this);
        break;
      case WAITING_ROOM:
        WaitingRoom::processEvents(event, m_window, *this);
        controller.initEnet();
        controller.processServer();
        break;
      case GAME:
        controller.processServer();
        break;
      default:
        break;
    }
  }
}

bool View::isOpen() const { return m_window.isOpen(); }


void View::display(const char* waitingMessage) {
  switch (m_currentMode) {
    case MENU:
      Menu::display(m_window);
      break;
    case WAITING_ROOM:
      WaitingRoom::display(m_window, waitingMessage);
      break;
    case GAME:
      break;
    default:
      break;
  }
}

void View::close() { m_window.close(); }
