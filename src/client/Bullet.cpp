#include "client/Bullet.hpp"
#include <cmath>

Bullet::Bullet(float startX, float startY, float angle, float customSpeed, sf::Color color) 
    : speed(customSpeed) 
{
    usesTexture = false;
    shape.setSize(sf::Vector2f(15.f, 5.f)); 
    shape.setFillColor(color);
    shape.setOrigin(7.5f, 2.5f);
    shape.setPosition(startX, startY);
    shape.setRotation(angle);

    float rad = angle * 3.14159f / 180.f;
    velocity = sf::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed);
}

Bullet::Bullet(float startX, float startY, float angle, float customSpeed, const sf::Texture& texture) 
    : speed(customSpeed) 
{
    usesTexture = true;
    sprite.setTexture(texture);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(startX, startY);
    sprite.setRotation(angle);
    sprite.setScale(0.1f, 0.1f);

    float rad = angle * 3.14159f / 180.f;
    velocity = sf::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed);
}

void Bullet::update(float deltaTime) {
    if (usesTexture) {
        sprite.move(velocity * deltaTime);
    } else {
        shape.move(velocity * deltaTime);
    }
}

void Bullet::draw(sf::RenderWindow &window) {
    if (usesTexture) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::FloatRect Bullet::getBounds() const {
    if (usesTexture) {
        return sprite.getGlobalBounds();
    }
    return shape.getGlobalBounds();
}

bool Bullet::isOffScreen() const {
    return lifetimeClock.getElapsedTime().asSeconds() > 3.0f;
}
