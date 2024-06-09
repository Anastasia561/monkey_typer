#include<algorithm>
#include <string>
#include <fmt/ranges.h>
#include "complexText.h"

#include <SFML/Graphics.hpp>

void ComplexText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(base, states);
    target.draw(typed, states);
}

auto ComplexText::highlight() -> void {
    auto typedChar = static_cast<char>(base.getString()[0]);
    std::string typedPart = typed.getString();
    typedPart += typedChar;
    std::string s2 = base.getString();
    std::ranges::reverse(s2);
    s2.pop_back();
    std::ranges::reverse(s2);
    base.setString(s2);
    typed.setString(typedPart);
    base.setPosition(typed.getLocalBounds().width + typed.getPosition().x, base.getPosition().y);

//    std::string base0 = base.getString();
//    std::string typed0 = typed.getString();
//    fmt::println(" base: {}", base0);
//    fmt::println("typed: {}", typed0);
}