#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

#include "client/Enemy.hpp"
#include <vector>
#include <map>
#include <memory>

struct EnemyType {
    std::string texturePath;
    EnemyStats stats;
};

class EnemyFactory {
public:
    static EnemyFactory& getInstance();
    
    // Initialise le registre des ennemis
    void init();
    
    // Crée un ennemi aléatoire dans la plage de puissance donnée
    std::unique_ptr<Enemy> createRandomEnemy(int minPower, int maxPower, float startX, float startY);
    
    // Crée un boss spécifique pour le niveau
    std::unique_ptr<Enemy> createBoss(int level, float startX, float startY);

private:
    EnemyFactory() = default;
    
    std::vector<EnemyType> enemyRegistry;
    std::map<int, EnemyType> bossRegistry;
    
    void registerEnemy(const std::string &name, int power, int hp, float speed, int points, const std::string &texture);
    void registerBoss(int level, const std::string &name, int hp, float speed, int points, const std::string &texture);
};

#endif // ENEMYFACTORY_HPP
