#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

auto main() -> int {
    auto window = sf::RenderWindow(
            sf::VideoMode(800, 600),
            "game",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );

    auto charSize = 20;
    auto lineNumber = 540 / (charSize + 30);

    auto words = std::vector<std::string>{
            "hello", "some", "different", "words", "in", "random", "order",
            "my", "new", "coat", "world", "worlds", "good", "bad", "never", "say"
    };

    auto fonts = std::vector<sf::Font>(5);
    fonts[0].loadFromFile("OpenSans.ttf");
    fonts[1].loadFromFile("Oswald.ttf");
    fonts[2].loadFromFile("Pacifico.ttf");
    fonts[3].loadFromFile("Tusj.ttf");
    fonts[4].loadFromFile("Seasrn.ttf");


    auto texts = std::vector<sf::Text>();
    for (auto word: words) {
        auto text = sf::Text();

        auto number = std::rand() % 5;
        text.setFont(fonts[number]);

        text.setString(word);
        text.setCharacterSize(charSize);
        //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
        // x ---> random [-300; 0]
        //i--> random : [0, linesNumber]
        //low + ( std::rand() % ( high - low + 1 ) )


        auto i = (1 + (std::rand() % lineNumber));
        auto y = i * (charSize + 30);

        auto x = 0;
        if (!texts.empty()) {
            for (auto item: texts) {
                if (item.getPosition().y == y) {
                    auto previousXPosition = item.getPosition().x;
                    x = previousXPosition - text.getLocalBounds().width - 100;
                }
            }
        } else {
            x = -300 + (std::rand() % 301);
        }

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
    auto x = 10;
    auto y = 540;
    labelEntering.setPosition(x, y);
    labelEntering.setFillColor(sf::Color::Red);
    labelEntering.setStyle(sf::Text::Bold | sf::Text::Underlined);


    auto textEntered = sf::Text();
    textEntered.setFont(labelFont);
    textEntered.setCharacterSize(24);
    textEntered.setPosition(200, y);
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
    labelCount.setPosition(630, 540);
    labelCount.setFillColor(sf::Color::Red);
    labelCount.setStyle(sf::Text::Bold | sf::Text::Underlined);

    auto counterText = sf::Text();
    counterText.setFont(labelFont);
    counterText.setCharacterSize(24);
    counterText.setPosition(labelCount.getPosition().x + labelCount.getLocalBounds().width + 20, 540);
    counterText.setFillColor(sf::Color::Red);
    counterText.setStyle(sf::Text::Bold);


    auto s = std::string();
    auto counter = 0;
    auto gameOver = false;

    while (window.isOpen()) {

        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (static_cast<char>(event.text.unicode) != 015) {
                    s += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    s = std::string();
                }
            }
        }

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
                text.move(0.03, 0);

                if (s == text.getString()) {
                    text.setFillColor(sf::Color::White);
                }
                //counter++;
                window.draw(text);
            }

            counterText.setString(std::to_string(counter));
            window.draw(textEntered);
            window.draw(labelEntering);
            window.draw(labelCount);
            //window.draw(counterText);

        } else {
            window.clear(sf::Color::White);
            window.draw(message);
        }
        window.display();
    }
}

