#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <string>

auto main() -> int {
    auto window = sf::RenderWindow(
            sf::VideoMode(800,600),
            "game",
            sf::Style::Default,
            sf::ContextSettings(0,0,8)
            );

    auto font = sf::Font();
    if (!font.loadFromFile("OpenSans.ttf")){
        fmt::println("{}", "Error while loading font");
    }

    auto text = sf::Text();

    text.setFont(font);
    text.setString("hello");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    auto s = std::string();
    while (window.isOpen()){
        for(auto event=sf::Event(); window.pollEvent(event);){
            if(event.type==sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::TextEntered){
                s+=static_cast<char>(event.text.unicode);
            }

            if (event.type == sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Enter){
                    s.clear();
                }
            }
        }

        text.move(0.01, 0);

        if(s==text.getString()){
            text.setFillColor(sf::Color::Green);
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }

}
