#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <set>

#include "creator.h"
#include "colors.h"
#include "fileProcessor.h"

auto generateXPosition(const std::vector<sf::Text> &texts, const sf::Text &text, int y) -> int;

auto updateBestScores(std::set<int> &bestScores, int currentScore) -> void;

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

    auto texts = wordsCreator(fonts, lineNumber, "words.txt");

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
                                  350, 200, sf::Color::Black);

    auto menuBlock = blockCreator(600, 50, 100, 30);

    auto optionsLabel = labelCreator(labelFont, 20,
                                     "show menu  -->  '1'\n\n"
                                     "start game  -->  '2'\n\nrise speed  -->  'arrow up'\n\n"
                                     "low speed  -->  'arrow down'",
                                     250, 260, sf::Color::Black);

    auto bestScoresLabel = labelCreator(labelFont, 24, "Best scores", 320, 300, sf::Color::Black);

    auto bestScoresOptions = labelCreator(labelFont, 20, "", 380, 350, sf::Color::Black);

    auto optionsFrame = frameCreator(400, 300, 200, 180);

    auto bestScoresFrame = frameCreator(200, 210, 290, 290);

    auto bestScores = std::set<int>();
    readFromFile(bestScores, "bestScores.txt");

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
                if (charEntered != 015 && charEntered != 061 && charEntered != 062 && charEntered != 010) {
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
                if (event.key.code == sf::Keyboard::BackSpace) {
                    s.erase(s.size() - 1);
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
        }
        window.display();
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
