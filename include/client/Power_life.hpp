#ifndef POWERLife_HPP
#define POWERLife_HPP

#include <SFML/Graphics.hpp>

class PowerLife {
public:
    PowerLife(const sf::Texture& texture, float x, float y) {
        life.setTexture(texture);
        sf::FloatRect bounds = life.getLocalBounds();
        life.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        life.setPosition(x, y);
        life.setScale(0.15f, 0.15f); // Taille ajustable
        spawnClock.restart();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(life);
    }

    sf::FloatRect getBounds() const {
        return life.getGlobalBounds();
    }

    bool isExpired() const {
        return spawnClock.getElapsedTime().asSeconds() > 40.f;
    }

private:
    sf::Sprite life;
    sf::Clock spawnClock;
};

#endif // POWERLife_HPP
