#pragma once

#include <string>
#include <SFML/Graphics.hpp>
//https://stackoverflow.com/questions/34458791/making-custom-types-drawable-with-sfml

class ComplexText : public sf::Drawable {
public:
    sf::Text base = sf::Text();
    sf::Text typed = sf::Text();

    auto setFont(sf::Font const &font) -> void {
        base.setFont(font);
        typed.setFont(font);
    };

    auto setSize(int size) -> void {
        base.setCharacterSize(size);
        typed.setCharacterSize(size);
    };

    auto setString(std::string const &s) -> void {
        base.setString(s);
        typed.setString("");
    };

    auto setPosition(int x, int y) -> void {
        typed.setPosition(x, y);
        base.setPosition( typed.getLocalBounds().width+x, y);
    };

    auto setFillColorTyped(sf::Color const &color) -> void {
        typed.setFillColor(color);
    };

    auto setFillColorBase(sf::Color const& color)->void{
        base.setFillColor(color);
    };

    auto getPositionY() const -> int {
        return typed.getPosition().y;
    };

    auto getPositionX() const -> int {
        return typed.getPosition().x;
    };

    auto getLocalBoundsWidth() const -> int {
        return typed.getLocalBounds().width + base.getLocalBounds().width;
    };

    auto getLocalBoundsHeight() const -> int {
        return typed.getLocalBounds().height;
    };

    auto getFillColor() const -> sf::Color {
        return typed.getFillColor();
    };

    auto getString() const -> std::string {
        return typed.getString() + base.getString();
    };

    auto move(float x, float y) -> void {
        typed.move(x, y);
        base.move(x, y);

    };

    auto highlight() -> void;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
