#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

class PowerUp {
public:
    PowerUp(const sf::Texture& texture, float x, float y) {
        sprite.setTexture(texture);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        sprite.setPosition(x, y);
        sprite.setScale(0.15f, 0.15f); // Taille ajustable
        spawnClock.restart();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    bool isExpired() const {
        return spawnClock.getElapsedTime().asSeconds() > 40.f;
    }

private:
    sf::Sprite sprite;
    sf::Clock spawnClock;
};

#endif // POWERUP_HPP
