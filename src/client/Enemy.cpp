#include "client/Enemy.hpp"
#include <iostream>
#include <cmath>
#include <memory>

Enemy::Enemy(const std::string &texturePath, const EnemyStats &stats, float startX, float startY)
    : stats(stats), currentHp(stats.hp), alive(true)
{
    // On initialise les munitions : 5 pour les ennemis normaux, "infini" (1000) pour le boss
    if (stats.name == "BOSS") {
        bulletsRemaining = 1000;
    } else {
        bulletsRemaining = 2; // Seulement 2 balles par ennemi
    }

    // On essaie de charger l'image
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur: Impossible de charger l'image : " << texturePath << std::endl;
    }
    
    sprite.setTexture(texture);
    
    // On définit le "centre" de l'image pour que les rotations ou positions soient plus simples
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
    // On place l'ennemi au point de départ
    sprite.setPosition(startX, startY);
    sprite.setRotation(180.f + 90.f); // Regarde vers la gauche (180) + offset nez (90)
    
    // On réduit un peu la taille de l'image
    sprite.setScale(0.2f, 0.2f); 
}

void Enemy::update(float deltaTime, const sf::Vector2f& targetPos) {
    if (!alive) return;
    movementTimer += deltaTime;
    
    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (stats.name == "BOSS") {
        // Le boss se déplace vers la gauche et s'arrête à une certaine position
        // Pour rester compatible avec la caméra, on pourrait le faire par rapport au joueur,
        // mais pour "rester comme avant", on reprend l'ancienne logique de X fixe.
        if (sprite.getPosition().x > 1400.f) {
            sprite.move(-stats.speed * deltaTime, 0.f);
        }
        
        // Mouvement sinusoïdal vertical
        float verticalMovement = std::sin(movementTimer * 2.f) * 150.f * deltaTime;
        sprite.move(0.f, verticalMovement);
        
        // Le boss regarde le joueur
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
        sprite.setRotation(angle);
    } else {
        // Les ennemis normaux foncent sur le joueur de tous les sens
        if (distance > 1.5f) {
            // /= divise les coordonnées par la distance pour obtenir un vecteur unitaire
            direction /= distance;
            sprite.move(direction * stats.speed * deltaTime);
            
            // Regarder le joueur
            float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
            sprite.setRotation(angle);
        }
    }
    // Si l'ennemi est vraiment trop loin du joueur (ex: le joueur s'est enfui), on le recycle
    if (distance > 2500.f) {
        alive = false;
    }
}

std::unique_ptr<Bullet> Enemy::shoot() {
    // Si l'ennemi ne peut pas tirer (fireRate = 0) ou n'a plus de balles
    if (stats.fireRate <= 0.f || bulletsRemaining <= 0) return nullptr;

    // Si le temps est écoulé pour le prochain tir
    if (shootClock.getElapsedTime().asSeconds() > stats.fireRate) {
        shootClock.restart();
        bulletsRemaining--; // On retire une balle
        
        sf::Vector2f pos = sprite.getPosition();
        float angle = sprite.getRotation(); // L'image pointe vers la droite (0 deg) par défaut
        float rad = angle * 3.14159f / 180.f;
        
        // Spawn au "nez" de l'ennemi (on ajuste l'offset selon la taille du sprite)
        float offset = 50.f; 
        pos.x += std::cos(rad) * offset;
        pos.y += std::sin(rad) * offset;
        
        // Créer la balle (si elle sort toujours de côté, essayez de changer 'angle' par 'sprite.getRotation()')
        auto bullet = std::make_unique<Bullet>(pos.x, pos.y, angle, 400.f, sf::Color::Red);
        return bullet;
    }
    return nullptr;
}

void Enemy::draw(sf::RenderWindow &window) {
    if (alive) {

        sf::Sprite shadow = sprite;
        shadow.setColor(sf::Color(0, 0, 0, 100));
        shadow.move(8.f, 8.f);
        window.draw(shadow);

        window.draw(sprite);
    }
}

sf::FloatRect Enemy::getBounds() const {
    // Retourne le rectangle de collision global (avec sa position actuelle)
    return sprite.getGlobalBounds();
}

bool Enemy::isAlive() const {
    // Il est vivant s'il n'est pas marqué mort ET qu'il lui reste de la vie
    return alive && currentHp > 0;
}

void Enemy::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp <= 0) {
        alive = false;
        std::cout << "Ennemi " << stats.name << " detruit ! Points : " << stats.points << std::endl;
    }
}

void Enemy::move(float dx, float dy) {
    if (alive) {
        sprite.move(dx, dy);
    }
}

