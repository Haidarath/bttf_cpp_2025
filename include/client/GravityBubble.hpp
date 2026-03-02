#ifndef GRAVITYBUBBLE_HPP
#define GRAVITYBUBBLE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "client/Enemy.hpp"

class GravityBubble {
public:
    GravityBubble(float x, float y);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    
    // Attirer les ennemis proches vers le centre
    void attractEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime);
    
    // Vérifier si une balle touche la bulle
    bool checkCollision(const sf::FloatRect& bulletBounds) const;
    
    // Tuer tous les ennemis à l'intérieur
    void Detonate(std::vector<std::unique_ptr<Enemy>>& enemies);
    
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::CircleShape dashedCircle;
    
    float radius;
    float attractionStrength;
    float dashRotation;
    
    // Pour l'effet de pointillés noirs
    std::vector<sf::RectangleShape> dashes;
    void setupDashes();
};

#endif // GRAVITYBUBBLE_HPP
