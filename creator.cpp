#include "complexText.h"
#include "fileProcessor.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <comdef.h>

auto labelCreator(const sf::Font &font, int size, const std::string &text, int x, int y,
                  const sf::Color &color) -> sf::Text {
    auto label = sf::Text();
    label.setFont(font);
    label.setCharacterSize(size);
    label.setString(text);
    label.setPosition(x, y);
    label.setFillColor(color);
    label.setStyle(sf::Text::Bold);
    return label;
}

auto fontsCreator() -> std::vector<sf::Font> {
    auto fonts = std::vector<sf::Font>(5);
    fonts[0].loadFromFile("OpenSans.ttf");
    fonts[1].loadFromFile("Oswald.ttf");
    fonts[2].loadFromFile("Pacifico.ttf");
    fonts[3].loadFromFile("Amatic.ttf");
    fonts[4].loadFromFile("Seasrn.ttf");
    return fonts;
}

auto generateXPosition(const std::vector<ComplexText> &texts, const ComplexText &text, int y) -> int {
    auto x = 0;
    auto space = (100 + (std::rand() % 301));
    if (!texts.empty()) {
        for (const auto &item: texts) {
            if (item.getPositionY() == y) {
                auto previousXPosition = item.getPositionX();
                x = previousXPosition - text.getLocalBoundsWidth() - space;
            }
        }
    } else {
        x = -200 + (std::rand() % 201);
    }
    return x;
}

auto savedWordsCreator(const std::vector<sf::Font> &fonts, const std::string &fileNameWords,
                       const std::string &fileNameCharSize,
                       const std::string &fileNamePositions) -> std::vector<ComplexText> {
    auto texts = std::vector<ComplexText>();
    auto file = std::fstream(fileNameWords);
    auto charSize = readCharSizeFromFile(fileNameCharSize);
    auto positions = readPositionsFromFile(fileNamePositions);
    auto i = 0;
    for (auto word = std::string(); file >> word;) {
        auto text = ComplexText();
        auto number = std::rand() % 5;
        text.setFont(fonts[number]);
        text.setString(word);
        text.setSize(charSize);

        auto x = positions[i].first;
        auto y = positions[i].second;

        text.setPosition(x, y);
        text.setFillColorBase(sf::Color(140, 210, 188));
        text.setFillColorTyped(sf::Color(255, 215, 0));
        texts.push_back(text);
        ++i;
    }
    return texts;
}

auto
wordsCreator(const std::vector<sf::Font> &fonts, int lineNumber, const std::string &fileName,
             int charSize) -> std::vector<ComplexText> {
    auto texts = std::vector<ComplexText>();
    auto file = std::fstream(fileName);
    for (auto word = std::string(); file >> word;) {
        auto text = ComplexText();
        auto number = std::rand() % 5;
        text.setFont(fonts[number]);
        text.setString(word);
        text.setSize(charSize);
        //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
        //low + ( std::rand() % ( high - low + 1 ) )

        auto lineSpace = (480 - (lineNumber * 40)) / lineNumber;
        auto randomLineNumber = (1 + (std::rand() % lineNumber));
        auto y = randomLineNumber * (40 + lineSpace);
        auto x = generateXPosition(texts, text, y);

        text.setPosition(x, y);
        text.setFillColorBase(sf::Color(140, 210, 188));
        text.setFillColorTyped(sf::Color(255, 215, 0));
        texts.push_back(text);
    }
    return texts;
}

auto frameCreator(const int &width, const int &height, const int &x, const int &y) -> sf::RectangleShape {
    auto frame = sf::RectangleShape(sf::Vector2f(width, height));
    frame.setPosition(x, y);
    frame.setFillColor(sf::Color(0, 0, 0, 0));
    frame.setOutlineThickness(5);
    frame.setOutlineColor(sf::Color::Blue);
    return frame;
}

auto blockCreator(const int &width, const int &height, const int &x, const int &y) -> sf::RectangleShape {
    auto block = sf::RectangleShape(sf::Vector2f(width, height));
    block.setPosition(x, y);
    block.setFillColor(sf::Color(135, 206, 250, 255));
    return block;
}
