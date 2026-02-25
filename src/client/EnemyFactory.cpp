#include "client/EnemyFactory.hpp"
#include <algorithm>
#include <random>
#include <iostream>

EnemyFactory& EnemyFactory::getInstance() {
    static EnemyFactory instance;
    return instance;
}

void EnemyFactory::init() {
    enemyRegistry.clear();
    
    // --- ENNEMIS FAIBLES (Power 1-3) ---
    registerEnemy("Drone", 1, 30, 100.f, 10, "sprites/enemies/basic_drone.png");
    registerEnemy("Scout", 2, 50, 150.f, 20, "sprites/enemies/fast_scout.gif");
    registerEnemy("Turret", 3, 80, 50.f, 30, "sprites/enemies/turret.png");
    
    // --- ENNEMIS MOYENS (Power 4-6) ---
    registerEnemy("Fighter", 4, 120, 120.f, 50, "sprites/enemies/enemy1.webp");
    registerEnemy("Tank", 5, 200, 60.f, 80, "sprites/enemies/heavy_tank.gif");
    registerEnemy("Stinger", 6, 150, 180.f, 100, "sprites/enemies/enemy2.gif");
    
    // --- ENNEMIS FORTS (Power 7-9) ---
    registerEnemy("Reaper", 7, 250, 140.f, 150, "sprites/enemies/enemy3.gif");
    registerEnemy("Vanguard", 8, 300, 110.f, 200, "sprites/enemies/enemy5.gif");
    registerEnemy("Interceptor", 9, 220, 220.f, 250, "sprites/enemies/enemy6.gif");

    // --- BOSS REGISTRY ---
    registerBoss(1, "Guardian", 1000, 40.f, 1000, "sprites/enemies/boss.gif");
    registerBoss(2, "Destroyer", 2500, 30.f, 2500, "sprites/enemies/boss1.webp");
}

void EnemyFactory::registerEnemy(const std::string &name, int power, int hp, float speed, int points, const std::string &texture) {
    EnemyType type;
    type.stats = {name, power, hp, speed, points};
    type.texturePath = texture;
    enemyRegistry.push_back(type);
}

void EnemyFactory::registerBoss(int level, const std::string &name, int hp, float speed, int points, const std::string &texture) {
    EnemyType type;
    type.stats = {name, 10, hp, speed, points}; // Power 10 par défaut pour les boss
    type.texturePath = texture;
    bossRegistry[level] = type;
}

std::unique_ptr<Enemy> EnemyFactory::createRandomEnemy(int minPower, int maxPower, float startX, float startY) {
    std::vector<EnemyType*> available;
    
    for (auto &type : enemyRegistry) {
        if (type.stats.powerLevel >= minPower && type.stats.powerLevel <= maxPower) {
            available.push_back(&type);
        }
    }
    
    if (available.empty()) {
        std::cerr << "Warning: No enemies found in power range " << minPower << "-" << maxPower << std::endl;
        return nullptr;
    }
    
    // Sélection aléatoire
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, available.size() - 1);
    
    EnemyType* chosen = available[dis(gen)];
    return std::make_unique<Enemy>(chosen->texturePath, chosen->stats, startX, startY);
}

std::unique_ptr<Enemy> EnemyFactory::createBoss(int level, float startX, float startY) {
    if (bossRegistry.find(level) == bossRegistry.end()) {
        // Fallback sur le boss 1 si non trouvé
        auto &boss = bossRegistry[1];
        return std::make_unique<Enemy>(boss.texturePath, boss.stats, startX, startY);
    }
    
    auto &boss = bossRegistry[level];
    return std::make_unique<Enemy>(boss.texturePath, boss.stats, startX, startY);
}
