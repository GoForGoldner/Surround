#include "game.h"

#include <iostream>
#include <sstream>

#include "controller.h"
#include "view.h"

Game::Game(int boardWidth, int boardHeight, int numberOfPlayers)
    : m_currentDireciton(Direction::DOWN),
      m_board(std::vector<std::vector<enet_uint32>>(
          boardHeight, std::vector<enet_uint32>(boardWidth, -1))) {}

void Game::processViewEvents(const sf::Event& event, sf::RenderWindow& window,
                             View& view, Controller& controller) {
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
      case sf::Keyboard::W:
        if (m_currentDireciton != Direction::DOWN &&
            m_currentDireciton != Direction::UP) {
          m_currentDireciton = Direction::UP;
          controller.sendDirection(m_currentDireciton);
          std::cout << "Moving Up" << std::endl;
        }
        break;
      case sf::Keyboard::A:
        if (m_currentDireciton != Direction::RIGHT &&
            m_currentDireciton != Direction::LEFT) {
          m_currentDireciton = Direction::LEFT;
          controller.sendDirection(m_currentDireciton);
          std::cout << "Moving Left" << std::endl;
        }
        break;
      case sf::Keyboard::S:
        if (m_currentDireciton != Direction::UP &&
            m_currentDireciton != Direction::DOWN) {
          m_currentDireciton = Direction::DOWN;
          controller.sendDirection(m_currentDireciton);
          std::cout << "Moving Down" << std::endl;
        }
        break;
      case sf::Keyboard::D:
        if (m_currentDireciton != Direction::LEFT &&
            m_currentDireciton != Direction::RIGHT) {
          m_currentDireciton = Direction::RIGHT;
          controller.sendDirection(m_currentDireciton);
          std::cout << "Moving Right" << std::endl;
        }
        break;
      default:
        break;
    }
  }
}

void Game::display(sf::RenderWindow& window) {
  window.clear();  // Clear the previous frame

  int rectWidth = window.getSize().x / m_board[0].size();
  int rectHeight = window.getSize().y / m_board.size();

  for (int row = 0; row < m_board.size(); ++row) {
    for (int col = 0; col < m_board[row].size(); ++col) {
      if (m_idToColor.find(m_board[row][col]) == m_idToColor.end()) {
        // Generate random RGB values (0–255)
        sf::Uint8 r = static_cast<sf::Uint8>(std::rand() % 256);
        sf::Uint8 g = static_cast<sf::Uint8>(std::rand() % 256);
        sf::Uint8 b = static_cast<sf::Uint8>(std::rand() % 256);

        m_idToColor[m_board[row][col]] = sf::Color(r, g, b);
      }

      sf::RectangleShape rect(sf::Vector2f(rectWidth, rectHeight));
      rect.setPosition(sf::Vector2f(rectWidth * col, rectHeight * row));

      rect.setFillColor(m_idToColor[m_board[row][col]]);

      window.draw(rect);
    }
  }

  window.display();
}

void Game::processServerEvents(const char* packet) {
  std::stringstream ss(packet);
  std::string line;

  while (std::getline(ss, line)) {
    std::stringstream lineStream(line);
    enet_uint32 id;
    size_t x, y;

    if (lineStream >> id >> x >> y) {
      std::cout << id << ":  " << x << ",  " << y << std::endl;
      std::cout << "Attempting to access: y=" << y << ", x=" << x << std::endl;
      std::cout << "Board dimensions: height=" << m_board.size()
                << ", width=" << (m_board.empty() ? 0 : m_board[0].size())
                << std::endl;
      m_board[y][x] = id;
      std::cout << "safe" << std::endl;
    } else {
      std::cerr << "Error parsing line: " << line << std::endl;
    }
  }
}