#include "client/Player.hpp"
#include "client/GameOverMenu.hpp"
#include <iostream>
#include <cmath>

Player::Player(const std::string &textureFile, float x, float y)
    : hp(10)
{
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Impossible de charger la texture: " + textureFile);
    }
    
    if (!forceTexture.loadFromFile("sprites/bouleforce.png")) {
        std::cerr << "Erreur: Impossible de charger sprites/bouleforce.png" << std::endl;
    }

    if (!lifeTexture.loadFromFile("sprites/life.png")) {
        std::cerr << "Erreur: Impossible de charger sprites/life.png" << std::endl;
    }

    if (hasForceActive) {
        sprite.setTexture(forceTexture);
    } else {
        sprite.setTexture(texture);
    }

    if (hasLifeActive) {
        sprite.setTexture(lifeTexture);
    } else {
        sprite.setTexture(texture);
    }
    
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(x, y);
    sprite.setRotation(0.f);
}

void Player::update(float deltaTime) {
    (void)deltaTime;
    
    if (isInvincible()) {
        sprite.setColor(sf::Color(255, 255, 255, 128));
    } else {
        sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    // Désactiver la force après 30 secondes
    if (hasForceActive && forceTimer.getElapsedTime().asSeconds() > 30.f) {
        hasForceActive = false;
        std::cout << "Force expi: Retour aux projectiles normaux." << std::endl;
    }
}

void Player::handleInput(const sf::Vector2f& mousePos) {
    float speed = 6.f;
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movement.x += 1.f;

    if (movement.x != 0.f || movement.y != 0.f) {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= length;
        this->move(movement.x * speed, movement.y * speed);
    }

    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f aimDir = mousePos - currentPos;
    float angle = std::atan2(aimDir.y, aimDir.x) * 180 / 3.14159f;
    sprite.setRotation(angle); 
}

std::unique_ptr<Bullet> Player::shoot() {
    float cooldown = hasForceActive ? 0.4f : 0.2f; 
    if (shootClock.getElapsedTime().asSeconds() > cooldown) {
        shootClock.restart();
        sf::Vector2f pos = sprite.getPosition();
        float angle = sprite.getRotation(); 
        float rad = angle * 3.14159f / 180.f;
        
        // Spawn au "sommet" (le nez)
        float offset = 50.f; 
        pos.x += std::cos(rad) * offset;
        pos.y += std::sin(rad) * offset;
        
        if (hasForceActive) {
            return std::make_unique<Bullet>(pos.x, pos.y, angle, 1000.f, forceTexture);
        } else {
            return std::make_unique<Bullet>(pos.x, pos.y, angle, 800.f);
        }
    }
    return nullptr;
}

void Player::move(float dx, float dy) {
    sprite.move(dx, dy);
}

void Player::setScale(float factor) {
    sprite.setScale(factor, factor);
}

void Player::draw(sf::RenderWindow &window) {
    sf::Sprite shadow = sprite;
    shadow.setColor(sf::Color(0, 0, 0, 100));
    shadow.move(10.f, 10.f);
    window.draw(shadow);
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::takeDamage() {
    if (!isInvincible()) {
        hp--;
        std::cout << "JOUEUR TOUCHE ! Vies restantes : " << hp << std::endl;
        if (hp > 0) invincibilityClock.restart();
    }
}

bool Player::isInvincible() const {
    return invincibilityClock.getElapsedTime().asSeconds() < 1.5f;
}

void Player::activateForce() {
    hasForceActive = true;
    forceTimer.restart();
    std::cout << "FORCE ACTIVEE pour 30 secondes !" << std::endl;
}

bool Player::isForceActive() const {
    return hasForceActive;
}

void Player::activateLife() {
    hasLifeActive = true;
    hp = hp + 3;
    std::cout << "VIE ACTIVEE pour 30 secondes !" << std::endl;
}

bool Player::isLifeActive() const {
    return hasLifeActive;
}

float Player::getForceTimeRemaining() const {
    if (!hasForceActive) return 0.f;
    float remaining = 30.f - forceTimer.getElapsedTime().asSeconds();
    return remaining > 0.f ? remaining : 0.f;
}
