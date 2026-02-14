#include "client/Background.hpp"
#include <iostream>

Background::Background(const std::string &textureFile, float x, float y)
{
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Impossible de charger la texture: " + textureFile);
    }

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Background::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
