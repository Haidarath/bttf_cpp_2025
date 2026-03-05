#include "client/Level.hpp"
#include <iostream>
#include <cmath>
#include "client/Sounds.hpp"
#include "client/BlasterWeapon.hpp"
#include "client/GravityLauncherWeapon.hpp"

Level::Level(const std::string &bgTexture, const std::string &playerTexture, int levelNum)
    : levelNumber(levelNum), background(bgTexture, 0.f, 0.f, true), player(playerTexture, 200.f, 1080.f / 2.f),
      spawnInterval(3.0f), enemiesToSpawn(15), bossSpawned(false), bossDefeated(false)
{
    // Objectif de mission : 200 points pour le Niveau 1
    objective = std::make_unique<MissionObjective>(200, 120.f);
    
    // Charger la police pour afficher les textes
    fontLoaded = false;
    if (font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Black.ttf")) {
        fontLoaded = true;
    }
    
    if (fontLoaded) {
        // Titre du niveau
        levelTitleText.setFont(font);
        levelTitleText.setString("NIVEAU " + std::to_string(levelNumber));
        levelTitleText.setCharacterSize(60);
        levelTitleText.setFillColor(sf::Color::White);
        levelTitleText.setPosition(50.f, 20.f);

        // Texte pour les points de vie
        hpText.setFont(font);
        hpText.setCharacterSize(40);
        hpText.setFillColor(sf::Color::Red);
        hpText.setPosition(50.f, 100.f);

        // Texte pour les bulles de gravité
        bubbleText.setFont(font);
        bubbleText.setCharacterSize(40);
        bubbleText.setFillColor(sf::Color::Blue);
        bubbleText.setPosition(50.f, 160.f);
    }
    player.setScale(0.2f);

    // Initialisation de la caméra et de l'UI
    camera.setSize(1920, 1080);
    camera.setCenter(player.getPosition());
    uiView.setSize(1920, 1080);
    uiView.setCenter(960, 540); // Milieu de l'écran (1920/2, 1080/2)

    if (explodeTexture.loadFromFile("sprites/effects/effect1.png")) {
        // La texture est prête, on l'utilisera quand on créera des explosions
    }

    if (!forceItemTexture.loadFromFile("sprites/force.png")) {
        std::cerr << "Erreur: Impossible de charger sprites/force.png" << std::endl;
    }
    
    if (!lifeItemTexture.loadFromFile("sprites/life.png")) {
        std::cerr << "Erreur: Impossible de charger sprites/life.png" << std::endl;
    }
    forceSpawnClock.restart();

    // Initialisation du système d'armes
    player.addWeapon(std::make_unique<BlasterWeapon>(bullets));
    player.addWeapon(std::make_unique<GravityLauncherWeapon>(gravityBubble));
}

void Level::spawnEnemy() {
    // Condition pour le boss : on a épuisé le quota d'ennemis ET le score est proche de l'objectif (200+)
    bool scoreCloseToTarget = (objective && objective->getCurrentScore() >= 200);

    if (enemiesToSpawn <= 0 && scoreCloseToTarget) {
        if (!bossSpawned) spawnBoss();
        return;
    }

    EnemyStats stats = {"Drone", 50, 150.f, 10, 2.5f}; 
    std::string texturePath = "sprites/enemies/basic_drone.png";

    // Un peu d'aléatoire pour varier les ennemis selon le niveau
    int randomType = rand() % 3;
    if (levelNumber == 1) {
        if (randomType == 0) {
            stats = {"Drone", 40, 100.f, 10, 3.0f}; // Plus lent
            texturePath = "sprites/enemies/basic_drone.png";
        } else {
            stats = {"Tourelle", 60, 40.f, 20, 2.0f}; // Très passif
            texturePath = "sprites/enemies/turret.png";
        }
    } else {
        stats = {"Chasseur", 100, 180.f, 50, 1.5f};
        texturePath = "sprites/enemies/fast_scout.gif";
    }

    // SPAWN CIRCULAIRE : On fait apparaître l'ennemi autour du joueur
    float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.f;
    float spawnDistance = 1200.f; // Juste en dehors de l'écran (1920x1080)
    
    sf::Vector2f playerPos = player.getPosition();
    float spawnX = playerPos.x + std::cos(angle) * spawnDistance;
    float spawnY = playerPos.y + std::sin(angle) * spawnDistance;

    auto enemy = std::make_unique<Enemy>(texturePath, stats, spawnX, spawnY);
    enemies.push_back(std::move(enemy));
    
    // On décrémente seulement si on a encore des ennemis en réserve
    if (enemiesToSpawn > 0) {
        enemiesToSpawn--;
    }
}

void Level::spawnBoss() {
    std::cout << "ALERTE : BOSS EN APPROCHE !" << std::endl;
    EnemyStats bossStats = {"BOSS", 150, 40.f, 1000, 0.5f}; // Le boss tire toutes les 0.5s maintenant
    // Le boss apparaît à droite et avance vers la gauche
    auto boss = std::make_unique<Enemy>("sprites/enemies/boss.png", bossStats, 1920.f + 200.f, 1080.f / 2.f);
    enemies.push_back(std::move(boss));
    bossSpawned = true;

    Sounds::getInstance().stopMusic();
    Sounds::getInstance().playMusic("BOSS");
}

void Level::update(float deltaTime, sf::RenderWindow &window) {
    // Calculer la position de la souris dans le monde (important car la vue bouge)
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, camera); // On utilise la vue 'camera'

    player.handleInput(worldPos);
    player.update(deltaTime);
    
    if (objective) objective->update(deltaTime);
    
    // La caméra suit le joueur de manière fluide (smooth follow)
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f currentCenter = camera.getCenter();
    
    // Interpolation linéaire pour un mouvement de caméra plus "cinématique"
    float lerpStrength = 0.05f; // Force de lerp (5%)
    //currentCenter.x + (playerPos.x - currentCenter.x) * lerpStrength
    //C'est la formule mathématique du LERP :
    //Position=Actuelle+(Cible−Actuelle)×Force
    //Au lieu d'aller directement sur le joueur, la caméra ne parcourt que 5% (0.05) 
    // de la distance qui la sépare de lui à chaque image. Cela crée un mouvement de lissage très agréable.
    camera.setCenter(
        currentCenter.x + (playerPos.x - currentCenter.x) * lerpStrength,
        currentCenter.y + (playerPos.y - currentCenter.y) * lerpStrength

    );
    
    // Le fond défile maintenant en fonction de la position du joueur pour créer un effet de profondeur
    background.updateOffset(playerPos.x, playerPos.y);

    if (gravityBubble) {
        gravityBubble->update(deltaTime);
        gravityBubble->attractEnemies(enemies, deltaTime);
    }

    // Tir
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        player.shoot(playerPos, player.getRotation());
    }

    // Changement d'arme
    static bool tabPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        if (!tabPressed) {
            player.switchWeapon();
            tabPressed = true;
        }
    } else {
        tabPressed = false;
    }

    // Rechargement
    static bool rPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        if (!rPressed) {
            player.reload();
            rPressed = true;
        }
    } else {
        rPressed = false;
    }
    
    // Mise à jour des projectiles
    for (auto it = bullets.begin(); it != bullets.end();) {
        (*it)->update(deltaTime);
        
        // --- NOUVEAU : Collision balle joueur -> Bulle de Gravité ---
        if (gravityBubble && gravityBubble->checkCollision((*it)->getBounds())) {
            std::cout << "Bulle explosée !" << std::endl;
            gravityBubble->Detonate(enemies);
            
            // Effet d'explosion visuel pour la bulle
            ExplosionEffect exp;
            exp.sprite.setTexture(explodeTexture);
            sf::FloatRect bounds = exp.sprite.getLocalBounds();
            exp.sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
            exp.sprite.setPosition(gravityBubble->getPosition());
            exp.sprite.setScale(2.0f, 2.0f); // Grosse explosion
            exp.lifetime = 0.6f;
            explosions.push_back(exp);
            
            Sounds::getInstance().playSound("EXPLOSION");
            
            gravityBubble.reset();
            it = bullets.erase(it);
            continue; 
        }

        if ((*it)->isOffScreen()) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    // Mise à jour du texte
    if (fontLoaded) {
        hpText.setString("VIES : " + std::to_string(player.getHp()));
        Weapon* w = player.getCurrentWeapon();
        if (w) {
            std::string ammoStr = w->getIsReloading() ? "RELOADING..." : std::to_string(w->getCurrentAmmo()) + "/" + std::to_string(w->getMaxAmmo());
            bubbleText.setString(w->getName() + " : " + ammoStr + " (TAB to swap)");
        }
    }

    // On fait apparaître un ennemi si le temps est écoulé
    if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
        spawnEnemy();
        spawnClock.restart();
    }

    // --- GESTION DU POWER-UP FORCE ---
    // On essaie d'en faire apparaître un toutes les 25 secondes si des apparitions restent
    if (forceSpawnsLeft > 0 && !forcePowerUp && forceSpawnClock.getElapsedTime().asSeconds() > 25.0f) {
        // Position aléatoire autour du joueur
        float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.f;
        float dist = 400.f + static_cast<float>(rand() % 400);
        sf::Vector2f pos = player.getPosition() + sf::Vector2f(std::cos(angle) * dist, std::sin(angle) * dist);
        
        forcePowerUp = std::make_unique<PowerUp>(forceItemTexture, pos.x, pos.y);
        forceSpawnClock.restart();
        forceSpawnsLeft--;
        std::cout << "Power-up FORCE apparaît ! (Restant : " << forceSpawnsLeft << ")" << std::endl;
    }

    if (forcePowerUp) {
        // Collision avec le joueur
        if (player.getBounds().intersects(forcePowerUp->getBounds())) {
            player.activateForce();
            Sounds::getInstance().playSound("PLAY"); // Petit son de confirmation
            forcePowerUp.reset();
        } 
        // Expiration après 40 secondes
        else if (forcePowerUp->isExpired()) {
            forcePowerUp.reset();
            std::cout << "Power-up expiré sans être ramassé." << std::endl;
        }
    }


    // --- GESTION DU POWER-UP VIE ---
    // On essaie d'en faire apparaître un toutes les 25 secondes si des apparitions restent
    if (lifeSpawnsLeft > 0 && !lifePowerUp && lifeSpawnClock.getElapsedTime().asSeconds() > 25.0f) {
        // Position aléatoire autour du joueur
        float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.f;
        float dist = 400.f + static_cast<float>(rand() % 400);
        sf::Vector2f pos = player.getPosition() + sf::Vector2f(std::cos(angle) * dist, std::sin(angle) * dist);
        
        lifePowerUp = std::make_unique<PowerUp>(lifeItemTexture, pos.x, pos.y);
        lifeSpawnClock.restart();
        lifeSpawnsLeft--;
        std::cout << "Power-up VIE apparaît ! (Restant : " << lifeSpawnsLeft << ")" << std::endl;
    }

    if (lifePowerUp) {
        // Collision avec le joueur
        if (player.getBounds().intersects(lifePowerUp->getBounds())) {
            player.activateLife();
            Sounds::getInstance().playSound("PLAY"); // Petit son de confirmation
            lifePowerUp.reset();
        } 
        // Expiration après 40 secondes
        else if (lifePowerUp->isExpired()) {
            lifePowerUp.reset();
            std::cout << "Power-up expiré sans être ramassé." << std::endl;
        }
    }

    // Mise à jour chaque ennemi, collisions et TIR
    bool someoneFiredThisFrame = false;
    float globalShootDelay = 3.0f; // Un peu plus actif mais reste raisonnable

    for (auto it = enemies.begin(); it != enemies.end();) {
        (*it)->update(deltaTime, playerPos);
        
        // --- NOUVEAU : Tentative de tir de l'ennemi (UN SEUL À LA FOIS) ---
        // --- Tir de l'ennemi ---
        // Le boss (points >= 1000) tire indépendamment du délai global
        bool isBoss = ((*it)->getPoints() >= 1000);
        bool canShoot = false;
        
        if (isBoss) {
            canShoot = true;
        } else if (!someoneFiredThisFrame && globalEnemyShootClock.getElapsedTime().asSeconds() > globalShootDelay) {
            canShoot = true;
            someoneFiredThisFrame = true;
            globalEnemyShootClock.restart();
        }

        if (canShoot) {
            auto eBullet = (*it)->shoot();
            if (eBullet) {
                enemyBullets.push_back(std::move(eBullet));
            }
        }

        // Si l'ennemi touche le joueur par contact physique
        if ((*it)->isAlive() && (*it)->getBounds().intersects(player.getBounds())) {
            player.takeDamage();
            Sounds::getInstance().playSound("HIT");
            
            // Créer une explosion
            ExplosionEffect exp;
            exp.sprite.setTexture(explodeTexture);
            sf::FloatRect bounds = exp.sprite.getLocalBounds();
            exp.sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
            exp.sprite.setPosition(player.getPosition());
            exp.sprite.setScale(0.5f, 0.5f);
            exp.lifetime = 0.3f; // Durée de 0.3 seconde
            explosions.push_back(exp);
        }
        
        // Si un projectile touche l'ennemi
        for (auto bit = bullets.begin(); bit != bullets.end();) {
            if ((*it)->isAlive() && (*it)->getBounds().intersects((*bit)->getBounds())) {
                int damage = (*bit)->isForce() ? 9999 : 10;
                (*it)->takeDamage(damage); 
                
                // Créer une explosion à l'endroit de l'impact
                ExplosionEffect exp;
                exp.sprite.setTexture(explodeTexture);
                sf::FloatRect bounds = exp.sprite.getLocalBounds();
                exp.sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
                exp.sprite.setPosition((*bit)->getBounds().left, (*bit)->getBounds().top);
                exp.sprite.setScale(0.3f, 0.3f);
                exp.lifetime = 0.2f;
                explosions.push_back(exp);

                bit = bullets.erase(bit); // Le projectile disparaît
            } else {
                ++bit;
            }
        }

        // Si l'ennemi est mort ou sorti de l'écran, on l'enlève de la liste
        if (!(*it)->isAlive()) {
            if (objective && (*it)->getCurrentHp() <= 0) { // Si tué par le joueur
                objective->addScore((*it)->getPoints());
                std::cout << "Ennemi " << (*it)->getPoints() << " detruit !" << std::endl;
                Sounds::getInstance().playSound("EXPLOSION");
                
                // Grosse explosion quand l'ennemi meurt
                ExplosionEffect exp;
                exp.sprite.setTexture(explodeTexture);
                sf::FloatRect bounds = exp.sprite.getLocalBounds();
                exp.sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
                exp.sprite.setPosition((*it)->getBounds().left + (*it)->getBounds().width/2.f, 
                                     (*it)->getBounds().top + (*it)->getBounds().height/2.f);
                exp.sprite.setScale(0.8f, 0.8f);
                exp.lifetime = 0.5f;
                explosions.push_back(exp);

                // Si c'était un boss, on le marque
                if ((*it)->getPoints() >= 1000) { // On assume que le boss donne bcp de points
                    bossDefeated = true;
                }
            }
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }

    // --- NOUVEAU : Mise à jour des projectiles ENNEMIS et collision avec JOUEUR ---
    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        (*it)->update(deltaTime);
        
        // Si le projectile ennemi touche le joueur
        if ((*it)->getBounds().intersects(player.getBounds())) {
            player.takeDamage();
            Sounds::getInstance().playSound("HIT");
            it = enemyBullets.erase(it);
        } else if ((*it)->isOffScreen()) {
            it = enemyBullets.erase(it);
        } else {
            ++it;
        }
    }

    // Mise à jour des explosions
    for (auto it = explosions.begin(); it != explosions.end();) {
        it->lifetime -= deltaTime;
        if (it->lifetime <= 0) {
            it = explosions.erase(it);
        } else {
            // Optionnel : faire clignoter ou réduire l'opacité
            sf::Color c = it->sprite.getColor();
            c.a = static_cast<sf::Uint8>((it->lifetime / 0.5f) * 255);
            it->sprite.setColor(c);
            ++it;
        }
    }
}

void Level::draw(sf::RenderWindow &window) {
    // 0. On efface l'écran (Vert pour le sol du Niveau 1, Noir sinon)
    if (levelNumber == 1) {
        window.clear(sf::Color(100, 130, 100)); // Un vert "sol" plus naturel
    } else {
        window.clear(sf::Color::Black);
    }

    // 1. Dessiner le fond d'abord. On utilise uiView pour qu'il remplisse toujours l'écran
    // et défile de manière fluide quel que soit le mouvement de la caméra.
    window.setView(uiView);
    background.draw(window);

    // 2. Dessiner le monde (avec la caméra qui suit le joueur)
    window.setView(camera);

    for (auto &enemy : enemies) {
        enemy->draw(window);
    }
    
    if (gravityBubble) {
        gravityBubble->draw(window);
    }
    
    for (auto &bullet : bullets) {
        bullet->draw(window);
    }

    for (auto &bullet : enemyBullets) {
        bullet->draw(window);
    }

    if (forcePowerUp) {
        forcePowerUp->draw(window);
    }

    if (lifePowerUp) {
        lifePowerUp->draw(window);
    }

    for (auto &exp : explosions) {
        window.draw(exp.sprite);
    }

    player.draw(window);

    // 3. Dessiner l'interface par-dessus tout
    window.setView(uiView);
    
    if (objective) objective->draw(window);

    if (fontLoaded) {
        window.draw(levelTitleText);
        window.draw(hpText);
        window.draw(bubbleText);
    }
}
