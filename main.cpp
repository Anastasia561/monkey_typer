#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>

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

    auto text = sf::Text();

    text.setFont(font);
    text.setString("hello");
    text.setCharacterSize(24);
    text.setPosition(-70, 20);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    auto text2 = sf::Text();

    text2.setFont(font);
    text2.setString("world");
    text2.setCharacterSize(24);
    text2.setPosition(-30, 60);
    text2.setFillColor(sf::Color::Red);
    text2.setStyle(sf::Text::Bold);


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
    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered && event.key.code != sf::Keyboard::Num1) {
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

        if ((text.getLocalBounds().width + text.getPosition().x) > 800) {
            window.clear(sf::Color::White);
            window.draw(message);
            window.display();
        } else {
            if (text.getPosition().x > 300 && text.getFillColor() != sf::Color::White) {
                text.setFillColor(sf::Color::Blue);
            }
            if (text2.getPosition().x > 300 && text.getFillColor() != sf::Color::White) {
                text2.setFillColor(sf::Color::Blue);
            }

            textEntered.setString(s);
            text.move(0.01, 0);
            text2.move(0.01, 0);

            if (s == text.getString()) {
                text.setFillColor(sf::Color::White);
            }
            if (s == text2.getString()) {
                text2.setFillColor(sf::Color::White);
            }

            window.clear(sf::Color::White);
            window.draw(text);
            window.draw(text2);
            window.draw(textEntered);
            window.draw(label);
            window.display();
        }
    }
}
