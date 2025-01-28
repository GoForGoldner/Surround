#include "text.h"

sf::Font text::loadFont(const char* fontPath) {
  sf::Font font;
  if (!font.loadFromFile(fontPath)) {
    std::cerr << "Error: Failed to load font!" << std::endl;
  }
  return font;
}

void text::displayText(std::string str, sf::Font font, int size, float xPercent,
                       float yPercent, float borderPadding, sf::Color color,
                       sf::RenderWindow& window) {
  // Create the title text
  sf::Text text;
  text.setString(str);  // Set your title text
  text.setFont(font);
  text.setCharacterSize(size);  // Larger font size for the title
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);

  // Calculate text bounds
  sf::FloatRect textBounds = text.getLocalBounds();

  // Adjust the origin and position of the text
  text.setOrigin(textBounds.left + textBounds.width / 2.f,
                 textBounds.top + textBounds.height / 2.f);
  text.setPosition(window.getSize().x * xPercent,
                   window.getSize().y * yPercent);

  // Create the rectangle background
  sf::RectangleShape rect;

  // Add border padding to the rectangle's size
  rect.setSize({textBounds.width + 2 * borderPadding * window.getSize().x,
                textBounds.height + 2 * borderPadding * window.getSize().y});
  rect.setFillColor(color);

  // Adjust the origin and position of the rectangle
  rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);
  rect.setPosition(text.getPosition());

  // Draw the rectangle (behind the text) and the text
  window.draw(rect);
  window.draw(text);
}

bool text::isMouseClickInRegion(const sf::Event& event, sf::RenderWindow& window,
                          float leftPercent, float topPercent,
                          float widthPercent, float heightPercent) {
  if (event.type == sf::Event::MouseButtonPressed) {
    // Get the size of the window
    sf::Vector2u windowSize = window.getSize();

    // Calculate the bounds of the region
    float left = leftPercent * windowSize.x;
    float top = topPercent * windowSize.y;
    float width = widthPercent * windowSize.x;
    float height = heightPercent * windowSize.y;

    // Get the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Check if the mouse position is within the bounds
    if (mousePos.x >= left && mousePos.x <= left + width && mousePos.y >= top &&
        mousePos.y <= top + height) {
      return true;
    }
  }
  return false;
}
