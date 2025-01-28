#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

namespace text {
sf::Font loadFont(const char* fontPath);

void displayText(std::string str, sf::Font font, int size, float xPercent,
                 float yPercent, float borderPadding, sf::Color color, sf::RenderWindow& window);

bool isMouseClickInRegion(const sf::Event& event, sf::RenderWindow& window,
                          float leftPercent, float topPercent,
                          float widthPercent, float heightPercent);
}  // namespace text