#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "client/Player.hpp"
#include "client/Background.hpp"
#include "client/Enemy.hpp"
#include "client/Bullet.hpp"
#include "client/MissionObjective.hpp"
#include "client/PowerUp.hpp"
#include "client/GravityBubble.hpp"

class Level {
public:
    Level(const std::string &bgTexture, const std::string &playerTexture, int levelNumber = 1);
    
    void update(float deltaTime, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    
    bool isGameOver() const { 
        return player.isDead() || (objective && objective->isFailed()); 
    }

    bool isLevelComplete() const {
        return objective && objective->isCompleted() && bossDefeated;
    }

private:
    int levelNumber;
    Background background;
    Player player;
    
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Bullet>> enemyBullets;
    
    sf::Text levelTitleText;
    sf::Text hpText;
    sf::Text bubbleText;
    sf::Font font;
    bool fontLoaded;
    
    sf::Clock spawnClock;
    float spawnInterval;
    int enemiesToSpawn;
    bool bossSpawned;
    bool bossDefeated;
    
    std::unique_ptr<MissionObjective> objective;
    
    sf::View camera;
    sf::View uiView;

    sf::Clock globalEnemyShootClock;

    void spawnEnemy();
    void spawnBoss();

    struct ExplosionEffect {
        sf::Sprite sprite;
        float lifetime;
    };
    std::vector<ExplosionEffect> explosions;
    sf::Texture explodeTexture;

    // Power-up Force
    std::unique_ptr<PowerUp> forcePowerUp;
    sf::Texture forceItemTexture;
    int forceSpawnsLeft = 3;
    sf::Clock forceSpawnClock;

    // Power-up Vie
    std::unique_ptr<PowerUp> lifePowerUp;
    sf::Texture lifeItemTexture;
    int lifeSpawnsLeft = 3;
    sf::Clock lifeSpawnClock;

    // Bulle de gravité (Touche B)
    std::unique_ptr<GravityBubble> gravityBubble;
    int gravityBubblesLeft = 3;
};

#endif // LEVEL_HPP
