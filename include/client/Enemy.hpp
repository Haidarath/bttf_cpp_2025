#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "client/Bullet.hpp"

// Structure simple pour stocker les caractéristiques d'un ennemi
struct EnemyStats {
    std::string name;   // Nom de l'ennemi (ex: "Drone")
    int hp;             // Points de vie
    float speed;        // Vitesse de déplacement
    int points;         // Points rapportés quand il meurt
    float fireRate;     // Cadence de tir (si 0, il ne tire pas)
};

class Enemy {
public:
    // Constructeur : initialise l'ennemi avec une image, des stats et une position
    Enemy(const std::string &texturePath, const EnemyStats &stats, float startX, float startY);
    
    // Met à jour la position de l'ennemi en ciblant une position (le joueur)
    void update(float deltaTime, const sf::Vector2f& targetPos);
    
    // Nouveau : l'ennemi tire
    std::unique_ptr<Bullet> shoot();

    // Dessine l'ennemi dans la fenêtre
    void draw(sf::RenderWindow &window);
    
    // Récupère la zone de collision (rectangle autour du sprite)
    sf::FloatRect getBounds() const;
    
    // Vérifie si l'ennemi est encore vivant
    bool isAlive() const;
    
    // Inflige des dégâts à l'ennemi
    void takeDamage(int damage);

    int getPoints() const { return stats.points; }
    int getCurrentHp() const { return currentHp; }

private:
    sf::Sprite sprite;      // L'image affichée à l'écran
    sf::Texture texture;    // La ressource image chargée en mémoire
    EnemyStats stats;       // Les stats (vie, vitesse...)
    int currentHp;          // Vie actuelle (baisse quand on reçoit des dégâts)
    bool alive;             // État de vie (true = vivant, false = mort)
    int bulletsRemaining;   // Nouveau : nombre de munitions (limité sauf pour le boss)
    float movementTimer = 0.f; // Pour les patterns de mouvement (ex: boss)
    sf::Clock shootClock;   // Pour gérer la cadence de tir
};

#endif // ENEMY_HPP
