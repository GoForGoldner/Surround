#include "menu.h"

#include <iostream>

#include "text.h"

void Menu::processEvents(const sf::Event& event, sf::RenderWindow& window, View& view) {
  // Play button
  if (text::isMouseClickInRegion(event,window, 0.0f, 0.0f, 0.5f, 0.5f)) {
    view.changeMode(View::Mode::WAITING_ROOM);
  }

  // Exit button
  if (text::isMouseClickInRegion(event,window, 0.0f, 0.0f, 0.0f, 0.0f)) {
  }
}

void Menu::display(sf::RenderWindow& window) {
  window.clear();  // Load the font

  sf::Font newYearGoo = text::loadFont(
      "C:"
      "\\Users\\tytyp\\Desktop\\Surround\\SurroundClient\\re"
      "sources\\NewyearGoo."
      "ttf");

  text::displayText("Surround", newYearGoo, 150, 0.5, 0.25, 0.02,
                    sf::Color(17, 15, 140), window);

  text::displayText("Play", newYearGoo, 45, 0.5, 0.5, 0.02,
                    sf::Color(17, 15, 140), window);

  text::displayText("Exit", newYearGoo, 45, 0.5, 0.6, 0.02,
                    sf::Color(17, 15, 140), window);

  // Display the frame
  window.display();
}