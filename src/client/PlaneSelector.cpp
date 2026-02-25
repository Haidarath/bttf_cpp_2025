#include "client/PlaneSelector.hpp"
#include <iostream>

PlaneSelector::PlaneSelector() {
    setupPlanes();
    setupText();
}

void PlaneSelector::setupPlanes() {
    // Charger les textures dans les variables membres
    if (!choosePlaneTexture.loadFromFile("sprites/choose_plane.png")) {
        throw std::runtime_error("Impossible de charger: sprites/choose_plane.png");
    }
    if (!plane1Texture.loadFromFile("sprites/plane1.png")) {
        throw std::runtime_error("Impossible de charger: sprites/plane1.png");
    }
    if (!plane2Texture.loadFromFile("sprites/plane2.png")) {
        throw std::runtime_error("Impossible de charger: sprites/plane2.png");
    }
    if (!plane3Texture.loadFromFile("sprites/plane3.png")) {
        throw std::runtime_error("Impossible de charger: sprites/plane3.png");
    }
    if (!plane4Texture.loadFromFile("sprites/plane4.png")) {
        throw std::runtime_error("Impossible de charger: sprites/plane4.png");
    }
    if (!plane5Texture.loadFromFile("sprites/plane5.png")) {
        throw std::runtime_error("Impossible de charger: sprites/plane5.png");
    }
    
    // Configuration du sprite de choix d'avion
    choosePlaneSprite.setTexture(choosePlaneTexture);
    sf::FloatRect chooseBounds = choosePlaneSprite.getLocalBounds();
    choosePlaneSprite.setOrigin(chooseBounds.width / 2.f, chooseBounds.height / 2.f);
    choosePlaneSprite.setPosition(1920.f / 2.f, 1080.f / 2.f);
    choosePlaneSprite.setScale(0.5f, 0.5f);

    // Configuration des 5 avions
    PlaneOption plane1, plane2, plane3, plane4, plane5;
    
    plane1.texturePath = "sprites/plane1.png";
    plane1.displayName = "Avion 1";
    plane1.sprite.setTexture(plane1Texture);
    
    plane2.texturePath = "sprites/plane2.png";
    plane2.displayName = "Avion 2";
    plane2.sprite.setTexture(plane2Texture);
    
    plane3.texturePath = "sprites/plane3.png";
    plane3.displayName = "Avion 3";
    plane3.sprite.setTexture(plane3Texture);
    
    plane4.texturePath = "sprites/plane4.png";
    plane4.displayName = "Avion 4";
    plane4.sprite.setTexture(plane4Texture);
    
    plane5.texturePath = "sprites/plane5.png";
    plane5.displayName = "Avion 5";
    plane5.sprite.setTexture(plane5Texture);
    
    // Centrer les sprites
    sf::FloatRect bounds1 = plane1.sprite.getLocalBounds();
    plane1.sprite.setOrigin(bounds1.width / 2.f, bounds1.height / 2.f);
    
    sf::FloatRect bounds2 = plane2.sprite.getLocalBounds();
    plane2.sprite.setOrigin(bounds2.width / 2.f, bounds2.height / 2.f);
    
    sf::FloatRect bounds3 = plane3.sprite.getLocalBounds();
    plane3.sprite.setOrigin(bounds3.width / 2.f, bounds3.height / 2.f);
    
    sf::FloatRect bounds4 = plane4.sprite.getLocalBounds();
    plane4.sprite.setOrigin(bounds4.width / 2.f, bounds4.height / 2.f);
    
    sf::FloatRect bounds5 = plane5.sprite.getLocalBounds();
    plane5.sprite.setOrigin(bounds5.width / 2.f, bounds5.height / 2.f);
    
    // Positionner les avions : 2 en haut, 3 en bas
    float centerX = 1920.f / 2.f;  // 960
    float centerY = 1080.f / 2.f;  // 540
    
    float horizontalSpacing = 150.f;  // Distance horizontale entre avions
    float verticalSpacing = 100.f;    // Distance verticale entre lignes
    
    // Rangée du haut (planes 1 et 2) - centrés
    plane1.sprite.setPosition(centerX - horizontalSpacing / 2.f, centerY - verticalSpacing);
    plane1.sprite.setScale(0.2f, 0.2f);
    
    plane2.sprite.setPosition(centerX + horizontalSpacing / 2.f, centerY - verticalSpacing);
    plane2.sprite.setScale(0.2f, 0.2f);
    
    // Rangée du bas (planes 3, 4, 5) - 3 avions espacés
    plane3.sprite.setPosition(centerX - horizontalSpacing, centerY + verticalSpacing);
    plane3.sprite.setScale(0.2f, 0.2f);
    
    plane4.sprite.setPosition(centerX, centerY + verticalSpacing);
    plane4.sprite.setScale(0.2f, 0.2f);
    
    plane5.sprite.setPosition(centerX + horizontalSpacing, centerY + verticalSpacing);
    plane5.sprite.setScale(0.2f, 0.2f);
    
    // Définir les zones cliquables
    float clickWidth = 300.f;
    float clickHeight = 300.f;
    
    plane1.clickZone = sf::FloatRect(
        centerX - horizontalSpacing / 2.f - clickWidth / 2.f,
        centerY - verticalSpacing - clickHeight / 2.f,
        clickWidth,
        clickHeight
    );
    
    plane2.clickZone = sf::FloatRect(
        centerX + horizontalSpacing / 2.f - clickWidth / 2.f,
        centerY - verticalSpacing - clickHeight / 2.f,
        clickWidth,
        clickHeight
    );
    
    plane3.clickZone = sf::FloatRect(
        centerX - horizontalSpacing - clickWidth / 2.f,
        centerY + verticalSpacing - clickHeight / 2.f,
        clickWidth,
        clickHeight
    );
    
    plane4.clickZone = sf::FloatRect(
        centerX - clickWidth / 2.f,
        centerY + verticalSpacing - clickHeight / 2.f,
        clickWidth,
        clickHeight
    );
    
    plane5.clickZone = sf::FloatRect(
        centerX + horizontalSpacing - clickWidth / 2.f,
        centerY + verticalSpacing - clickHeight / 2.f,
        clickWidth,
        clickHeight
    );
    
    planes.push_back(plane1);
    planes.push_back(plane2);
    planes.push_back(plane3);
    planes.push_back(plane4);
    planes.push_back(plane5);
}

void PlaneSelector::setupText() {
    std::cout << "=== Menu de sélection d'avion ===" << std::endl;
    std::cout << "Cliquez sur l'avion de votre choix" << std::endl;
    
    // Essayer de charger une police système
    fontLoaded = false;
    
    // Essayer plusieurs polices Black (très épaisses) sur Linux
    std::vector<std::string> fontPaths = {
        "/usr/share/fonts/truetype/noto/NotoSans-Black.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"
    };
    
    for (const auto& fontPath : fontPaths) {
        if (font.loadFromFile(fontPath)) {
            fontLoaded = true;
            std::cout << "Police chargée: " << fontPath << std::endl;
            break;
        }
    }
    
    if (fontLoaded) {
        // Texte de bienvenue
        welcomeText.setFont(font);
        welcomeText.setString("Bienvenue");
        welcomeText.setCharacterSize(80);
        welcomeText.setFillColor(sf::Color::White);
        welcomeText.setStyle(sf::Text::Bold);
        
        // Centrer le texte
        sf::FloatRect textBounds = welcomeText.getLocalBounds();
        welcomeText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        welcomeText.setPosition(1920.f / 2.f, 200.f);
        
        // Texte d'instruction
        instructionText.setFont(font);
        instructionText.setString("Choisissez votre avion");
        instructionText.setCharacterSize(40);
        instructionText.setFillColor(sf::Color::White);
        
        sf::FloatRect instrBounds = instructionText.getLocalBounds();
        instructionText.setOrigin(instrBounds.width / 2.f, instrBounds.height / 2.f);
        instructionText.setPosition(1920.f / 2.f, 300.f);
    } else {
        std::cout << "Aucune police trouvée, le texte ne sera pas affiché" << std::endl;
    }
}

void PlaneSelector::draw(sf::RenderWindow &window) {
    // Fond bleu clair pour le menu
    window.clear(sf::Color(135, 206, 235)); // Sky blue
    
    // Dessiner le texte de bienvenue si la police est chargée
    if (fontLoaded) {
        window.draw(welcomeText);
        window.draw(instructionText);
    }
    
    // Dessiner le sprite de choix d'avion (en arrière-plan)
    window.draw(choosePlaneSprite);
    
    // Dessiner les deux avions
    for (auto &plane : planes) {
        window.draw(plane.sprite);
    }
}

void PlaneSelector::update(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    for (auto &plane : planes) {
        if (plane.clickZone.contains(mousePos)) {
            plane.sprite.setScale(0.25f, 0.25f); // Agrandir au survol
        } else {
            plane.sprite.setScale(0.2f, 0.2f);
        }
    }
}

bool PlaneSelector::handleClick(float mouseX, float mouseY, std::string &selectedPlane) {
    sf::Vector2f mousePos(mouseX, mouseY);
    
    for (const auto &plane : planes) {
        if (plane.clickZone.contains(mousePos)) {
            selectedPlane = plane.texturePath;
            std::cout << "Avion sélectionné: " << plane.displayName 
                      << " (" << plane.texturePath << ")" << std::endl;
            return true;
        }
    }
    
    return false;
}
