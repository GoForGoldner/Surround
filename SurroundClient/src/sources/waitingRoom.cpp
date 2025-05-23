#include "waitingRoom.h"
#include "view.h"
#include "controller.h"

#include "iostream"
#include "text.h"

WaitingRoom::WaitingRoom() : m_waitingMessage("") {}

void WaitingRoom::processViewEvents(const sf::Event& event,
                                    sf::RenderWindow& window, View& view,
                                    Controller& controller) {}

void WaitingRoom::display(sf::RenderWindow& window) {
  window.clear();  // Load the font

  sf::Font newYearGoo = text::loadFont(
      "C:"
      "\\Users\\tytyp\\Desktop\\Surround\\SurroundClient\\re"
      "sources\\NewyearGoo."
      "ttf");

  text::displayText("Waiting...", newYearGoo, 100, 0.2f, 0.05f, 0.0f,
                    sf::Color::Black, window);

  text::displayText(m_waitingMessage, newYearGoo, 45, 0.22f, 0.18f, 0.0f,
                    sf::Color::Black, window);

  // Display the frame
  window.display();
}

void WaitingRoom::processServerEvents(const char* packet) {
  m_waitingMessage = std::string(packet, strlen(packet));
}

// static sf::Clock clocker;

//// Load the shader
// sf::Shader shader;
// if (!shader.loadFromFile("C:"
//                          "\\Users\\tytyp\\Desktop\\Surround\\SurroundClient\\"
//                          "resources\\background.frag",
//                          sf::Shader::Fragment)) {
//   std::cerr << "Error: Failed to load fragment shader!" << std::endl;
//   return;
// }
//
//// Create a clock to track elapsed time
// static sf::Clock clocker;
//
//// Set shader uniforms
// shader.setUniform("resolution",
//                   sf::Vector2f(window.getSize().x, window.getSize().y));
// shader.setUniform("time", clocker.getElapsedTime().asSeconds());
//
//// Draw the shader as a fullscreen background
// sf::RectangleShape fullscreenQuad(sf::Vector2f(window.getSize().x,
//                                                window.getSize().y));
// fullscreenQuad.setPosition(0, 0);
// window.draw(fullscreenQuad, &shader);