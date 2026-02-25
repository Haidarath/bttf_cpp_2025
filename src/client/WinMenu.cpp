#include "client/WinMenu.hpp"
#include <iostream>

WinMenu::WinMenu() {
    // Charger la police
    if (!font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Black.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police pour le menu Victoire" << std::endl;
    }

    // Titre "MISSION RÉUSSIE"
    titleText.setFont(font);
    titleText.setString("MISSION REUSSIE");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::Green);
    titleText.setStyle(sf::Text::Bold);
    
    // Centrer le titre
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titleText.setPosition(1920.f / 2.f, 300.f);

    setupButtons();
}

void WinMenu::setupButtons() {
    float startY = 500.f;
    float spacing = 120.f;

    std::vector<std::pair<std::string, WinAction>> buttonData = {
        {"CONTINUER", WinAction::Continue},
        {"RECOMMENCER", WinAction::Retry},
        {"MENU PRINCIPAL", WinAction::MainMenu}
    };

    for (size_t i = 0; i < buttonData.size(); ++i) {
        WinButton btn;
        btn.action = buttonData[i].second;

        // Configuration visuelle du bouton
        btn.shape.setSize(sf::Vector2f(600.f, 80.f));
        btn.shape.setFillColor(sf::Color(50, 150, 50)); // Vert sombre
        btn.shape.setOutlineThickness(3.f);
        btn.shape.setOutlineColor(sf::Color::White);
        
        // Centrer le bouton
        btn.shape.setOrigin(300.f, 40.f);
        btn.shape.setPosition(1920.f / 2.f, startY + i * spacing);

        // Texte du bouton
        btn.text.setFont(font);
        btn.text.setString(buttonData[i].first);
        btn.text.setCharacterSize(40);
        btn.text.setFillColor(sf::Color::White);
        
        sf::FloatRect textBounds = btn.text.getLocalBounds();
        btn.text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        btn.text.setPosition(btn.shape.getPosition());

        btn.clickZone = btn.shape.getGlobalBounds();
        buttons.push_back(btn);
    }
}

void WinMenu::draw(sf::RenderWindow &window) {
    // On dessine un fond noir un peu transparent par dessus le jeu
    sf::RectangleShape overlay(sf::Vector2f(1920.f, 1080.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    window.draw(titleText);
    for (auto &btn : buttons) {
        window.draw(btn.shape);
        window.draw(btn.text);
    }
}

WinAction WinMenu::handleClick(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    for (const auto &btn : buttons) {
        if (btn.clickZone.contains(mousePos)) {
            return btn.action;
        }
    }
    return WinAction::None;
}

void WinMenu::handleMouseMove(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    for (auto &btn : buttons) {
        if (btn.clickZone.contains(mousePos)) {
            btn.shape.setFillColor(sf::Color(0, 200, 0)); // Vert brillant au survol
        } else {
            btn.shape.setFillColor(sf::Color(50, 150, 50));
        }
    }
}
