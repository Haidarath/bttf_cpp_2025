#include "client/Player.hpp"
#include <iostream>

Player::Player(const std::string &textureFile, float x, float y)
{
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Impossible de charger la texture: " + textureFile);
    }

    sprite.setTexture(texture);
    
    // Centrer l'avion
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(x, y);
}

void Player::update() {
    // Rien à faire pour l'instant vu qu'il n'y a plus d'animation
}

void Player::handleInput() {
    float speed = 5.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->move(0, -speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->move(0, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->move(speed, 0);
    }
}

void Player::move(float dx, float dy) {
    sprite.move(dx, dy);
}

void Player::setScale(float factor) {
    sprite.setScale(factor, factor);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
