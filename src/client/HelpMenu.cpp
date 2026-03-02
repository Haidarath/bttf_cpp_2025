#include "client/HelpMenu.hpp"
#include <iostream>

HelpMenu::HelpMenu() {
    buttonColor = sf::Color(70, 130, 180);
    buttonHoverColor = sf::Color(100, 149, 237);
    
    setupFont();
    setupContent();
}

void HelpMenu::setupFont() {
    fontLoaded = false;
    if (font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Black.ttf")) {
        fontLoaded = true;
    }
}

void HelpMenu::setupContent() {
    if (!fontLoaded) return;

    // Titre
    titleText.setFont(font);
    titleText.setString("GUIDE DE JEU");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titleText.setPosition(1920.f / 2.f, 100.f);

    // Contenu de l'aide
    std::vector<std::string> lines = {
        "COMMENT JOUER :",
        "- Deplacement : Touches DIRECTIONNELLES (Haut, Bas, Gauche, Droite)",
        "- Viser : Deplacez la SOURIS, l'avion suit le curseur",
        "- Tirer : CLIC GAUCHE sur l'ennemi",
        "",
        "VOTRE MISSION :",
        "- Survivez aux vagues d'ennemis (Drones et Tourelles)",
        "- Attention : Chaque ennemi a  2 balles, puis ils vous foncent dessus !",
        "- Attention : Le Boss a 1000 balles, et il bouge du haut vers le bas",
        "- Detruisez le BOSS final et ayez 200 points pour gagner le niveau",
        "",
        "BUT DU JEU :",
        "- Atteignez le score requis et eliminez la menace ennemie",
        "- Ne perdez pas toutes vos vies (vous commencez avec 10)",
        "",
        "BONUS :",
        "- Coeurs : Apparaissent aleatoirement et rendent 3 VIES au contact",
        "- Boule de feu : Transforme vos tirs en SUPER BALLES (tue en 1 coup)",
        "- Touche B : Cree une bulle (max 3) qui ATTIRE les ennemis. Tirez dessus pour tout exploser !"
    };

    float startY = 180.f;  
    float lineSpacing = 38.f; 
    for (const auto& line : lines) {
        sf::Text text;
        text.setFont(font);
        text.setString(line);
        text.setCharacterSize(22); 
        
        if (line.find(":") != std::string::npos && line.find("-") == std::string::npos) {
            text.setFillColor(sf::Color::Cyan);
            text.setStyle(sf::Text::Bold);
        } else {
            text.setFillColor(sf::Color::White);
        }

        // Centrer chaque ligne horizontalement
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2.f, 0.f);
        text.setPosition(1920.f / 2.f, startY);
        
        helpLines.push_back(text);
        startY += lineSpacing;
    }

    // Bouton Retour
    backButton.setSize(sf::Vector2f(300.f, 60.f));
    backButton.setFillColor(buttonColor);
    backButton.setOutlineColor(sf::Color::White);
    backButton.setOutlineThickness(2.f);
    backButton.setPosition(1920.f / 2.f - 150.f, 900.f);

    backText.setFont(font);
    backText.setString("RETOUR");
    backText.setCharacterSize(30);
    backText.setFillColor(sf::Color::White);
    sf::FloatRect bBounds = backText.getLocalBounds();
    backText.setOrigin(bBounds.width / 2.f, bBounds.height / 2.f);
    backText.setPosition(1920.f / 2.f, 930.f);

    backClickZone = sf::FloatRect(1920.f / 2.f - 150.f, 900.f, 300.f, 60.f);
}

void HelpMenu::draw(sf::RenderWindow &window) {
    window.clear(sf::Color(20, 20, 40));
    
    if (fontLoaded) {
        window.draw(titleText);
        for (const auto& text : helpLines) {
            window.draw(text);
        }
        window.draw(backButton);
        window.draw(backText);
    }
}

bool HelpMenu::handleClick(float mouseX, float mouseY) {
    if (backClickZone.contains(mouseX, mouseY)) {
        return true;
    }
    return false;
}

void HelpMenu::handleMouseMove(float mouseX, float mouseY) {
    if (backClickZone.contains(mouseX, mouseY)) {
        backButton.setFillColor(buttonHoverColor);
    } else {
        backButton.setFillColor(buttonColor);
    }
}
