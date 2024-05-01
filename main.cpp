#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>

auto fontsCreator() -> std::vector<sf::Font>;

auto generateXPosition(const std::vector<sf::Text> &texts, const sf::Text &text, int y) -> int;

auto labelCreator(const sf::Font &font, int size, std::string text, int x, int y, sf::Color color) -> sf::Text;

namespace color {
    auto backgroundColor1 = sf::Color(228, 246, 248);
    auto backgroundColor2 = sf::Color(0, 71, 100);
    auto wordColorNormal = sf::Color(140, 210, 188);
    auto wordColorDanger = sf::Color(255, 136, 73);
    auto blockColor = sf::Color(135, 206, 250, 255);
}

auto main() -> int {
    auto window = sf::RenderWindow(
            sf::VideoMode(800, 600),
            "game",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );

    auto lineNumber = 6;
    auto fonts = fontsCreator();
    auto labelFont = sf::Font();
    labelFont.loadFromFile("OpenSans.ttf");
    auto file = std::fstream("words.txt");

    auto texts = std::vector<sf::Text>();
    for (auto word = std::string(); file >> word;) {
        auto text = sf::Text();
        auto number = std::rand() % 5;
        text.setFont(fonts[number]);
        text.setString(word);
        auto charSize = 20 + (std::rand() % (40 - 20 + 1));
        text.setCharacterSize(charSize);
        //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
        //low + ( std::rand() % ( high - low + 1 ) )

        auto lineSpace = (480 - (lineNumber * 40)) / lineNumber;
        auto randomLineNumber = (1 + (std::rand() % lineNumber));
        auto y = randomLineNumber * (40 + lineSpace);
        auto x = generateXPosition(texts, text, y);

        text.setPosition(x, y);
        text.setFillColor(color::wordColorNormal);
        texts.push_back(text);
    }

    auto footer = sf::RectangleShape(sf::Vector2f(800, 60));
    footer.setPosition(0, 540);
    footer.setFillColor(color::blockColor);


    auto labelEntering = labelCreator(labelFont, 24, "Text you enter: ", 10, 560, sf::Color::Black);


    auto textEntered = labelCreator(labelFont, 24, "",
                                    labelEntering.getPosition().x + labelEntering.getLocalBounds().width + 10, 560,
                                    sf::Color::Black);


    auto endGameMessage = labelCreator(labelFont, 30, "GAME OVER", 300, 200, sf::Color::Black);
    auto endGameBlock = sf::RectangleShape(sf::Vector2f(300, 60));
    endGameBlock.setPosition(250, 190);
    endGameBlock.setFillColor(color::blockColor);


    auto labelCount = labelCreator(labelFont, 24, "Score: ", 530, 560, sf::Color::Black);


    auto counterText = labelCreator(labelFont, 24, "",
                                    labelCount.getPosition().x + labelCount.getLocalBounds().width + 20, 560,
                                    sf::Color::Black);


    auto titleLabel = labelCreator(labelFont, 30, "MONKEY TYPER", 260, 35, sf::Color::Black);
    auto menuLabel = labelCreator(labelFont, 24, "Menu", 350, 200, sf::Color::Black);
    auto optionsLabel = labelCreator(labelFont, 20,
                                     "show menu  -->  '1'\n\n"
                                     "start game  -->  '2'\n\nrise speed  -->  'arrow up'\n\nlow speed  -->  'arrow down'",
                                     250, 260, sf::Color::Black);

    auto menuBlock = sf::RectangleShape(sf::Vector2f(600, 50));
    menuBlock.setPosition(100, 30);
    menuBlock.setFillColor(color::blockColor);

    auto optionsFrame = sf::RectangleShape(sf::Vector2f(400, 300));
    optionsFrame.setPosition(200, 180);
    optionsFrame.setFillColor(sf::Color(0, 0, 0, 0));
    optionsFrame.setOutlineThickness(5);
    optionsFrame.setOutlineColor(sf::Color::Blue);

    auto s = std::string();
    auto counter = 0.0;
    auto speed = 0.05;
    auto gameOver = false;
    auto showMenu = true;
    auto riseSpeed = false;
    auto lowSpeed = false;


    while (window.isOpen()) {

        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                auto charEntered = static_cast<char>(event.text.unicode);
                if (charEntered != 015 && charEntered != 061 && charEntered != 062) {
                    s += charEntered;
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    s = std::string();
                }
                if (event.key.code == sf::Keyboard::Num1) {
                    showMenu = true;
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    showMenu = false;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    riseSpeed = true;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    lowSpeed = true;
                }
            }
        }

        window.clear(color::backgroundColor1);

        if (showMenu) {
            window.draw(menuBlock);
            window.draw(optionsFrame);
            window.draw(titleLabel);
            window.draw(menuLabel);
            window.draw(optionsLabel);
        } else {

            if (!gameOver) {
                window.clear(color::backgroundColor2);

                for (auto &text: texts) {

                    if ((text.getLocalBounds().width + text.getPosition().x) > 800 &&
                        text.getFillColor() != color::backgroundColor2) {
                        gameOver = true;
                    }

                    if (text.getPosition().x > 600 && text.getFillColor() != color::backgroundColor2) {
                        text.setFillColor(color::wordColorDanger);
                    }

                    if (riseSpeed) {
                        speed *= 2;
                        riseSpeed = false;
                    }
                    if (lowSpeed) {
                        speed /= 2;
                        lowSpeed = false;
                    }

                    textEntered.setString(s);
                    text.move(speed, 0);

                    if (s == text.getString()) {
                        text.setFillColor(color::backgroundColor2);
                    }

                    window.draw(text);
                }

                counter += 0.008;
                counterText.setString(std::to_string(static_cast<int>(counter)));

                window.draw(footer);
                window.draw(textEntered);
                window.draw(labelEntering);
                window.draw(labelCount);
                window.draw(counterText);

            } else {
                window.clear(color::backgroundColor1);
                window.draw(endGameBlock);
                window.draw(endGameMessage);
                labelCount.setPosition(330, 300);
                counterText.setPosition(430, 300);
                window.draw(counterText);
                window.draw(labelCount);
            }
        }
        window.display();
    }
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

auto generateXPosition(const std::vector<sf::Text> &texts, const sf::Text &text, int y) -> int {
    auto x = 0;
    auto space = (100 + (std::rand() % 301));
    if (!texts.empty()) {
        for (const auto &item: texts) {
            if (item.getPosition().y == y) {
                auto previousXPosition = item.getPosition().x;
                x = previousXPosition - text.getLocalBounds().width - space;
            }
        }
    } else {
        x = -200 + (std::rand() % 201);
    }
    return x;
}

auto labelCreator(const sf::Font &font, int size, std::string text, int x, int y, sf::Color color) -> sf::Text {
    auto label = sf::Text();
    label.setFont(font);
    label.setCharacterSize(size);
    label.setString(text);
    label.setPosition(x, y);
    label.setFillColor(color);
    label.setStyle(sf::Text::Bold);
    return label;
}
