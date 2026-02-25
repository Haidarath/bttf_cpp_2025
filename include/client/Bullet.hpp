#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet {
public:
    // Constructeurs avec vitesse ajustable
    Bullet(float startX, float startY, float angle, float customSpeed, sf::Color color = sf::Color::Yellow);
    Bullet(float startX, float startY, float angle, float customSpeed, const sf::Texture& texture);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    sf::FloatRect getBounds() const;
    
    bool isOffScreen() const;
    bool isForce() const { return usesTexture; }

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    bool usesTexture = false;
    
    float speed;
    sf::Vector2f velocity;
    sf::Clock lifetimeClock;
};

#endif // BULLET_HPP
