#include <fmt/core.h>
#include <SFML/Graphics.hpp>

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
    text.setString("Hello world");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

//    auto circle = sf::CircleShape(100, 100);
//    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()){
        for(auto event=sf::Event(); window.pollEvent(event);){
            if(event.type==sf::Event::Closed){
                window.close();
            }
        }



        text.move(0.01, 0);

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }

}
