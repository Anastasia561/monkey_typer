#include <fmt/ranges.h>
#include "complexText.h"

#include <SFML/Graphics.hpp>

void ComplexText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(base, states);
    target.draw(typed, states);
}
