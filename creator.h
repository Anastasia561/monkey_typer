#pragma once

#include "complexText.h"
#include <SFML/Graphics.hpp>

auto labelCreator(const sf::Font &font, int size, const std::string &text, int x, int y,
                  const sf::Color &color) -> sf::Text;

auto fontsCreator() -> std::vector<sf::Font>;

auto
wordsCreator(const std::vector<sf::Font> &fonts, int lineNumber, const std::string &fileName,
             int charSize) -> std::vector<ComplexText>;

auto savedWordsCreator(const std::vector<sf::Font> &fonts, const std::string &fileNameWords,
                       const std::string &fileNameCharSize,
                       const std::string &fileNamePositions) -> std::vector<ComplexText>;

auto frameCreator(const int &width, const int &height, const int &x, const int &y) -> sf::RectangleShape;

auto blockCreator(const int &width, const int &height, const int &x, const int &y) -> sf::RectangleShape;
