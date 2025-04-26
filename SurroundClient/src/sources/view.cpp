#include "view.h"

#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
#include <iostream>

#include "controller.h"

View::View(Menu& menu, WaitingRoom& waitingRoom, Game& game)
    : m_window(sf::RenderWindow({1280u, 720u}, "CMake SFML Project")),
      m_currentMode(Mode::MENU),
      m_idToColor(),
      m_menu(menu),
      m_waitingRoom(waitingRoom),
      m_game(game) {
  m_window.setFramerateLimit(144);
  m_idToColor[-1] = sf::Color::Black;
  m_idToColor[0] = sf::Color::White;
}

void View::changeMode(Mode mode) {
  std::cout << "Switching mode from " << m_currentMode << " to " << mode
            << std::endl;
  m_currentMode = mode;
}

void View::processEvents(Controller& controller) {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    }

    switch (m_currentMode) {
      case MENU:
        m_menu.processViewEvents(event, m_window, *this, controller);
        break;
      case WAITING_ROOM:
        m_waitingRoom.processViewEvents(event, m_window, *this, controller);
        break;
      case GAME: {
        m_game.processViewEvents(event, m_window, *this, controller);
      } break;
      default:
        break;
    }
  }
}

bool View::isOpen() const { return m_window.isOpen(); }

void View::close() { m_window.close(); }

void View::display() {
  switch (m_currentMode) {
    case MENU:
      m_menu.display(m_window);
      break;
    case WAITING_ROOM:
      m_waitingRoom.display(m_window);
      break;
    case GAME:
      m_game.display(m_window);
      break;
    default:
      break;
  }
}
