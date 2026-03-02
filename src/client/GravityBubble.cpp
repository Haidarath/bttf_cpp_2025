#include "client/GravityBubble.hpp"
#include <cmath>
#include <iostream>

GravityBubble::GravityBubble(float x, float y) {
    if (!texture.loadFromFile("sprites/bulle.png")) {
        std::cerr << "Erreur: Impossible de charger sprites/bulle.png" << std::endl;
    }
    sprite.setTexture(texture);
    
    // Centrer le sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(x, y);
    sprite.setScale(0.8f, 0.8f); 
    sprite.setColor(sf::Color(255, 255, 255, 180)); // Semi-transparent (180/255)
    
    radius = (bounds.width / 2.f) * 0.8f; // Rayon réel de la bulle
    attractionStrength = 320.f; // Pixels par seconde vers le centre
    dashRotation = 0.f;
    
    // Pour l'effet de pointillés noirs
    int numDashes = 18;
    float dashWidth = 12.f;
    float dashHeight = 4.f;
    
    for (int i = 0; i < numDashes; ++i) {
        sf::RectangleShape dash;
        dash.setSize(sf::Vector2f(dashWidth, dashHeight));
        dash.setOrigin(dashWidth / 2.f, dashHeight / 2.f);
        dash.setFillColor(sf::Color::Black);
        dashes.push_back(dash);
    }
    
    update(0.f); 
}

void GravityBubble::update(float deltaTime) {
    dashRotation += 80.f * deltaTime; // Faire tourner les tirets
    
    float dashRadius = radius + 15.f;
    for (size_t i = 0; i < dashes.size(); ++i) {
        float angle = (i * 360.f / dashes.size()) + dashRotation;
        float angleRad = (angle * 3.14159265f / 180.f);
        
        float dx = std::cos(angleRad) * dashRadius;
        float dy = std::sin(angleRad) * dashRadius;
        
        dashes[i].setPosition(getPosition().x + dx, getPosition().y + dy);
        dashes[i].setRotation(angle);
    }
}

void GravityBubble::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    for (const auto& dash : dashes) {
        window.draw(dash);
    }
}

void GravityBubble::attractEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) {
    sf::Vector2f center = getPosition();
    float attractRadius = 800.f; // Rayon d'attraction assez large
    
    for (auto& enemy : enemies) {
        if (!enemy->isAlive()) continue;
        // Ne pas attirer le BOSS (points >= 1000)
        if (enemy->getPoints() >= 1000) continue;
        
        sf::FloatRect eb = enemy->getBounds();
        sf::Vector2f enemyPos(eb.left + eb.width / 2.f, eb.top + eb.height / 2.f);
        
        sf::Vector2f diff = center - enemyPos;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        
        if (dist > 15.f && dist < attractRadius) {
            sf::Vector2f moveDir = (diff / dist) * attractionStrength * deltaTime;
            enemy->move(moveDir.x, moveDir.y);
        }
    }
}

void GravityBubble::Detonate(std::vector<std::unique_ptr<Enemy>>& enemies) {
    sf::Vector2f center = getPosition();
    float killRadius = radius + 30.f; // Un peu plus que le visuel
    
    for (auto& enemy : enemies) {
        if (!enemy->isAlive()) continue;
        if (enemy->getPoints() >= 1000) continue; // Pas le boss
        
        sf::FloatRect eb = enemy->getBounds();
        sf::Vector2f enemyPos(eb.left + eb.width / 2.f, eb.top + eb.height / 2.f);
        
        sf::Vector2f diff = center - enemyPos;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        
        if (dist < killRadius) {
            enemy->takeDamage(9999); // Mort instantanée
        }
    }
}

bool GravityBubble::checkCollision(const sf::FloatRect& bulletBounds) const {
    return getBounds().intersects(bulletBounds);
}

