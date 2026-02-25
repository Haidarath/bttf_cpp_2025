#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "client/Bullet.hpp"

class Player {
public:
    Player(const std::string &textureFile, float x, float y);

    void update(float deltaTime);
    void handleInput(const sf::Vector2f& mousePos);
    void move(float dx, float dy);
    void setScale(float factor);
    
    std::unique_ptr<Bullet> shoot();
    void draw(sf::RenderWindow &window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setRotation(float angle) { sprite.setRotation(angle); }
    
    int getHp() const { return hp; }
    void takeDamage();
    bool isInvincible() const;
    bool isDead() const { return hp <= 0; }

    // Power-up Force
    void activateForce();
    bool isForceActive() const;
    void activateLife();
    bool isLifeActive() const;
    float getForceTimeRemaining() const;

private:
    sf::Texture texture;
    sf::Texture forceTexture;
    sf::Texture lifeTexture;
    sf::Sprite sprite;
    
    int hp;
    sf::Clock invincibilityClock;
    sf::Clock shootClock;
    bool hasLifeActive = false;
    bool hasForceActive = false;
    sf::Clock forceTimer;
};

#endif // PLAYER_HPP
