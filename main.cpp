#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

#include "creator.h"
#include "colors.h"
#include "fileProcessor.h"

auto generateXPosition(const std::vector<sf::Text> &texts, const sf::Text &text, int y) -> int;

auto checkMousePosition(int mouseX, int mouseY, const sf::RectangleShape &button) -> bool;

auto updateBestScores(std::set<int> &bestScores, int currentScore) -> void;

auto findLastWord(const std::vector<sf::Text> &texts) -> sf::Text;

auto main() -> int {
    auto startWindow = sf::RenderWindow(
            sf::VideoMode(800, 600),
            "start",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );

    auto lineNumber = 6;
    auto fonts = fontsCreator();
    auto labelFont = sf::Font();
    labelFont.loadFromFile("OpenSans.ttf");

    auto footer = blockCreator(800, 60, 0, 540);


    auto labelEntering = labelCreator(labelFont,
                                      24, "Text you enter: ",
                                      10, 560, sf::Color::Black);


    auto textEntered = labelCreator(labelFont, 24, "",
                                    labelEntering.getPosition().x + labelEntering.getLocalBounds().width + 10,
                                    560, sf::Color::Black);


    auto endGameMessage = labelCreator(labelFont, 30, "GAME OVER",
                                       300, 100, sf::Color::Black);

    auto endGameBlock = blockCreator(300, 60, 250, 90);


    auto labelCount = labelCreator(labelFont, 24, "Score: ",
                                   530, 560, sf::Color::Black);


    auto counterText = labelCreator(labelFont, 24, "",
                                    labelCount.getPosition().x + labelCount.getLocalBounds().width + 20,
                                    560, sf::Color::Black);


    auto titleLabel = labelCreator(labelFont, 30, "MONKEY TYPER",
                                   260, 35, sf::Color::Black);

    auto menuLabel = labelCreator(labelFont, 24, "Menu",
                                  350, 160, sf::Color::Black);

    auto menuBlock = blockCreator(600, 50, 100, 30);

    auto optionsLabel = labelCreator(labelFont, 20,
                                     "rise speed  -->  'arrow up'\n\n"
                                     "low speed  -->  'arrow down'",
                                     250, 220, sf::Color::Black);

    auto bestScoresLabel = labelCreator(labelFont, 24, "Best scores", 320, 300, sf::Color::Black);

    auto bestScoresOptions = labelCreator(labelFont, 20, "", 380, 350, sf::Color::Black);

    auto optionsFrame = frameCreator(400, 250, 200, 140);

    auto bestScoresFrame = frameCreator(200, 210, 290, 290);

    auto fontSizeText = labelCreator(labelFont, 20, "", 430, 540, sf::Color::Black);
    auto fontSizeLabel = labelCreator(labelFont, 20, "Enter font size: ", 260, 540, sf::Color::Black);

    auto button = sf::RectangleShape();
    button.setSize(sf::Vector2f(160, 40));
    button.setPosition(300, 430);
    button.setFillColor(sf::Color::Blue);
    button.setOutlineThickness(3);
    button.setOutlineColor(sf::Color::Black);

    auto buttonLabel = labelCreator(labelFont, 20, "Start", 350, 440, sf::Color::White);


    auto bestScores = std::set<int>();
    readFromFile(bestScores, "bestScores.txt");

    auto s = std::string();
    auto f = std::string();
    auto counter = 0.0;
    auto speed = 0.05;
    auto gameOver = false;
    auto riseSpeed = false;
    auto lowSpeed = false;


    while (startWindow.isOpen()) {
        for (auto event = sf::Event(); startWindow.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                startWindow.close();
            }
            if (event.type == sf::Event::TextEntered) {
                auto charEntered = static_cast<char>(event.text.unicode);
                if (charEntered != 015 && charEntered != 010) {
                    f += charEntered;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed
                && checkMousePosition(sf::Mouse::getPosition(startWindow).x,
                                      sf::Mouse::getPosition(startWindow).y, button)) {
                startWindow.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    f.erase(f.size() - 1);
                }
            }
        }

        startWindow.clear(color::backgroundColor1);

        fontSizeText.setString(f);
        startWindow.draw(fontSizeText);
        startWindow.draw(fontSizeLabel);

        startWindow.draw(button);
        startWindow.draw(buttonLabel);

        startWindow.draw(menuBlock);
        startWindow.draw(optionsFrame);
        startWindow.draw(titleLabel);
        startWindow.draw(menuLabel);
        startWindow.draw(optionsLabel);

        startWindow.display();
    }

    auto charSize = 25;
    if (!f.empty()) {
        charSize = std::stoi(f);
    }
    auto texts = wordsCreator(fonts, lineNumber, "words.txt", charSize);

    if (!startWindow.isOpen()) {

        auto window = sf::RenderWindow(
                sf::VideoMode(800, 600),
                "game",
                sf::Style::Default,
                sf::ContextSettings(0, 0, 8)
        );

        while (window.isOpen()) {

            for (auto event = sf::Event(); window.pollEvent(event);) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::TextEntered) {
                    auto charEntered = static_cast<char>(event.text.unicode);
                    if (charEntered != 015 && charEntered != 010) {
                        s += charEntered;
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        s = std::string();
                    }

                    if (event.key.code == sf::Keyboard::Up) {
                        riseSpeed = true;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        lowSpeed = true;
                    }
                    if (event.key.code == sf::Keyboard::BackSpace) {
                        s.erase(s.size() - 1);
                    }
                }
            }


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

                if (findLastWord(texts).getFillColor() == color::backgroundColor2) {
                    gameOver = true;
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
                labelCount.setPosition(330, 200);
                counterText.setPosition(430, 200);

                updateBestScores(bestScores, static_cast<int>(counter));

                auto bestScoresOptionsString = std::string();
                for (auto score: bestScores) {
                    bestScoresOptionsString += std::to_string(score) + "\n\n";
                }

                bestScoresOptions.setString(bestScoresOptionsString);
                window.draw(bestScoresLabel);
                window.draw(bestScoresOptions);
                window.draw(counterText);
                window.draw(labelCount);
                window.draw(bestScoresFrame);
            }
            window.display();
        }
    }
    safeToFile(bestScores, "bestScores.txt");
}

auto updateBestScores(std::set<int> &bestScores, int currentScore) -> void {
    if (bestScores.size() < 3) {
        bestScores.insert(currentScore);
    } else {
        for (auto score: bestScores) {
            if (currentScore > score) {
                bestScores.erase(bestScores.begin());
                bestScores.insert(currentScore);
            }
        }
    }
}

auto checkMousePosition(int mouseX, int mouseY, const sf::RectangleShape &button) -> bool {
    auto buttonXLeft = button.getPosition().x;
    auto buttonXRight = button.getLocalBounds().width + buttonXLeft;
    auto buttonYUpper = button.getPosition().y;
    auto buttonYLower = button.getLocalBounds().height + buttonYUpper;

    return (mouseX > buttonXLeft && mouseX < buttonXRight && mouseY > buttonYUpper && mouseY < buttonYLower);
}

auto findLastWord(const std::vector<sf::Text> &texts) -> sf::Text {
    auto result = texts;
    auto projection = [](const auto &text) -> float {
        return text.getPosition().x;
    };
    std::ranges::sort(result, {}, projection);
    return result.front();
}
