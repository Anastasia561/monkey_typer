#pragma once

#include <SFML/Graphics.hpp>

auto labelCreator(const sf::Font &font, int size, const std::string &text, int x, int y,
                  const sf::Color &color) -> sf::Text;

auto fontsCreator() -> std::vector<sf::Font>;

auto
wordsCreator(const std::vector<sf::Font> &fonts, int lineNumber, const std::string &fileName) -> std::vector<sf::Text>;

auto frameCreator(const int &width, const int &height, const int &x, const int &y) -> sf::RectangleShape;

auto blockCreator(const int &width, const int &height, const int &x, const int &y) -> sf::RectangleShape;
