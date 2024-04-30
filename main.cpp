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

    auto font = sf::Font();
    if (!font.loadFromFile("OpenSans.ttf")) {
        fmt::println("{}", "Error while loading font");
    }

    auto charSize = 20;
//    auto lineNumber = 750 / 20;
//    auto lines = std::vector<std::vector<std::string>>(lineNumber);
//    for (auto& vec: lines) {
//        vec.push_back("world");
//    }
//    for (auto i = 0; i < lines.size(); ++i) {
//        lines[i].push_back("world" + i);
//    }

    auto texts = std::vector<sf::Text>();
    for (auto i = 0; i < 6; ++i) {
//        for (auto item: lines[i]) {
        auto text = sf::Text();
        text.setFont(font);
        text.setString(fmt::format("hello{}", i));
        text.setCharacterSize(charSize);
        //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range (range: [-20; 0] ---> (-20 + ( std::rand() % ( 0 + 20 + 1 ) ))
        text.setPosition((-400 + (std::rand() % (0 + 400 + 1))), i * (charSize + 30));
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        texts.push_back(text);
        //}
    }

    auto label = sf::Text();
    label.setFont(font);
    label.setCharacterSize(24);
    label.setString("Text you enter: ");
    auto x = 10;
    auto y = 540;
    label.setPosition(x, y);
    label.setFillColor(sf::Color::Red);
    label.setStyle(sf::Text::Bold | sf::Text::Underlined);


    auto textEntered = sf::Text();
    textEntered.setFont(font);
    textEntered.setCharacterSize(24);
    textEntered.setPosition(200, y);
    textEntered.setFillColor(sf::Color::Red);
    textEntered.setStyle(sf::Text::Bold);


    auto message = sf::Text();
    message.setFont(font);
    message.setCharacterSize(24);
    message.setString("Game over");
    message.setPosition(300, 300);
    message.setFillColor(sf::Color::Red);
    message.setStyle(sf::Text::Bold);


    auto s = std::string();
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
                text.move(0.01, 0);

                if (s == text.getString()) {
                    text.setFillColor(sf::Color::White);
                }

                window.draw(text);
            }

            window.draw(textEntered);
            window.draw(label);

        } else {
            window.clear(sf::Color::White);
            window.draw(message);
        }
        window.display();
    }
}
