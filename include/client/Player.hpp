#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "client/Bullet.hpp"
#include "client/Weapon.hpp"

class Player {
public:
    Player(const std::string &textureFile, float x, float y);

    void update(float deltaTime);
    void handleInput(const sf::Vector2f& mousePos);
    void move(float dx, float dy);
    void setScale(float factor);
    
    void addWeapon(std::unique_ptr<Weapon> weapon);
    void switchWeapon();
    void reload();
    void shoot(sf::Vector2f pos, float angle);
    Weapon* getCurrentWeapon();
    void draw(sf::RenderWindow &window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    float getRotation() const { return sprite.getRotation(); }
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
    
    std::vector<std::unique_ptr<Weapon>> weapons;
    int currentWeaponIndex = 0;
    
    bool hasLifeActive = false;
    bool hasForceActive = false;
    sf::Clock forceTimer;
};

#endif // PLAYER_HPP
