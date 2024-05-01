#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>

auto fontsCreator() -> std::vector<sf::Font>;

auto generateXPosition(const std::vector<sf::Text> &texts, const sf::Text &text, int y) -> int;

auto main() -> int {
    auto window = sf::RenderWindow(
            sf::VideoMode(800, 600),
            "game",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );

    auto charSize = 20;
    auto lineNumber = 540 / (charSize + 30);

    auto fonts = fontsCreator();

    auto file = std::fstream("words.txt");

    auto texts = std::vector<sf::Text>();
    for (auto word = std::string(); file >> word;) {
        auto text = sf::Text();
        auto number = std::rand() % 5;
        text.setFont(fonts[number]);
        text.setString(word);
        text.setCharacterSize(charSize);
        //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
        //low + ( std::rand() % ( high - low + 1 ) )

        auto randomLineNumber = (1 + (std::rand() % lineNumber));
        auto y = randomLineNumber * (charSize + 30);
        auto x = generateXPosition(texts, text, y);

        text.setPosition(x, y);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        texts.push_back(text);
    }

    auto labelFont = sf::Font();
    labelFont.loadFromFile("OpenSans.ttf");

    auto labelEntering = sf::Text();
    labelEntering.setFont(labelFont);
    labelEntering.setCharacterSize(24);
    labelEntering.setString("Text you enter: ");
    labelEntering.setPosition(10, 540);
    labelEntering.setFillColor(sf::Color::Red);
    labelEntering.setStyle(sf::Text::Bold | sf::Text::Underlined);


    auto textEntered = sf::Text();
    textEntered.setFont(labelFont);
    textEntered.setCharacterSize(24);
    textEntered.setPosition(labelEntering.getPosition().x + labelEntering.getLocalBounds().width + 10, 540);
    textEntered.setFillColor(sf::Color::Red);
    textEntered.setStyle(sf::Text::Bold);


    auto message = sf::Text();
    message.setFont(labelFont);
    message.setCharacterSize(24);
    message.setString("Game over");
    message.setPosition(300, 300);
    message.setFillColor(sf::Color::Red);
    message.setStyle(sf::Text::Bold);

    auto labelCount = sf::Text();
    labelCount.setFont(labelFont);
    labelCount.setCharacterSize(24);
    labelCount.setString("Score: ");
    labelCount.setPosition(530, 540);
    labelCount.setFillColor(sf::Color::Red);
    labelCount.setStyle(sf::Text::Bold | sf::Text::Underlined);

    auto counterText = sf::Text();
    counterText.setFont(labelFont);
    counterText.setCharacterSize(24);
    counterText.setPosition(labelCount.getPosition().x + labelCount.getLocalBounds().width + 20, 540);
    counterText.setFillColor(sf::Color::Red);
    counterText.setStyle(sf::Text::Bold);

    auto startLabel = sf::Text();
    startLabel.setFont(labelFont);
    startLabel.setCharacterSize(24);
    startLabel.setString("MENU\nto start game press '2'\nto open menu again press '1'\nto rise speed press '3'");
    startLabel.setPosition(300, 300);
    startLabel.setFillColor(sf::Color::Red);
    startLabel.setStyle(sf::Text::Bold);


    auto s = std::string();
    auto counter = 0.0;
    auto speed = 0.007;
    auto gameOver = false;
    auto showMenu = true;
    auto riseSpeed = false;


    while (window.isOpen()) {

        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                auto charEntered = static_cast<char>(event.text.unicode);
                if (charEntered != 015 && charEntered != 061 && charEntered != 062 && charEntered != 063) {
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
                if (event.key.code == sf::Keyboard::Num3) {
                    riseSpeed = true;
                }
            }

        }

        window.clear(sf::Color::White);

        if (showMenu) {
            window.draw(startLabel);
        } else {
            if (!gameOver) {
                window.clear(sf::Color::White);


                for (auto &text: texts) {

                    if ((text.getLocalBounds().width + text.getPosition().x) > 800 &&
                        text.getFillColor() != sf::Color::White) {
                        gameOver = true;
                    }

                    if (text.getPosition().x > 600 && text.getFillColor() != sf::Color::White) {
                        text.setFillColor(sf::Color::Blue);
                    }

                    textEntered.setString(s);

                    if (riseSpeed) {
                        speed *= 2;
                        text.move(speed, 0);
                        riseSpeed = false;
                    }
                    text.move(speed, 0);

                    if (s == text.getString()) {
                        text.setFillColor(sf::Color::White);
                    }

                    window.draw(text);
                }

                counter += 0.001;
                counterText.setString(std::to_string(static_cast<int>(counter)));

                window.draw(textEntered);
                window.draw(labelEntering);
                window.draw(labelCount);
                window.draw(counterText);

            } else {
                window.clear(sf::Color::White);
                window.draw(message);
                labelCount.setPosition(300, 400);
                counterText.setPosition(400, 400);
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
    fonts[3].loadFromFile("Tusj.ttf");
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
        x = -300 + (std::rand() % 301);
    }
    return x;
}


