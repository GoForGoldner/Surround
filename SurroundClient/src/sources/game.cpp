#include "game.h"
#include "controller.h"
#include <iostream>

void Game::processEvents(const sf::Event& event, sf::RenderWindow& window, 
                               View& view, Controller& controller) {
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
      case sf::Keyboard::W:
        if (m_currentDireciton != Direction::DOWN &&
            m_currentDireciton != Direction::UP) {
          m_currentDireciton = Direction::UP;
          controller.sendDirection(peer, m_currentDireciton);
          std::cout << "Moving Up" << std::endl;
        }
        break;
      case sf::Keyboard::A:
        if (m_currentDireciton != Direction::RIGHT &&
            m_currentDireciton != Direction::LEFT) {
          m_currentDireciton = Direction::LEFT;
          controller.sendDirection(peer, m_currentDireciton);
          std::cout << "Moving Left" << std::endl;
        }
        break;
      case sf::Keyboard::S:
        if (m_currentDireciton != Direction::UP &&
            m_currentDireciton != Direction::DOWN) {
          m_currentDireciton = Direction::DOWN;
          controller.sendDirection(peer, m_currentDireciton);
          std::cout << "Moving Down" << std::endl;
        }
        break;
      case sf::Keyboard::D:
        if (m_currentDireciton != Direction::LEFT &&
            m_currentDireciton != Direction::RIGHT) {
          m_currentDireciton = Direction::RIGHT;
          controller.sendDirection(peer, m_currentDireciton);
          std::cout << "Moving Right" << std::endl;
        }
        break;
      default:
        break;
    }
  }
}

void Game::display(sf::RenderWindow& window) {}