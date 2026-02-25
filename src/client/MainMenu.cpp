#include "client/MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu() {
    // Couleurs modernes pour le menu
    buttonColor = sf::Color(70, 130, 180);        // Steel blue
    buttonHoverColor = sf::Color(100, 149, 237);  // Cornflower blue
    buttonTextColor = sf::Color::White;
    
    setupFont();
    setupTitle();
    setupButtons();
}

void MainMenu::setupFont() {
    fontLoaded = false;
    
    // Essayer de charger une police système
    std::vector<std::string> fontPaths = {
        "/usr/share/fonts/truetype/noto/NotoSans-Black.ttf",
        "/usr/share/fonts/truetype/noto/NotoSans-Bold.ttf",
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
    
    if (!fontLoaded) {
        std::cout << "Aucune police trouvée, le texte ne sera pas affiché" << std::endl;
    }
}

void MainMenu::setupTitle() {
    if (!fontLoaded) return;
    
    titleText.setFont(font);
    titleText.setString("R-TYPE SHOOTER");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    
    // Centrer le titre
    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    titleText.setPosition(1920.f / 2.f, 200.f);
}

void MainMenu::setupButtons() {
    if (!fontLoaded) return;
    
    float centerX = 1920.f / 2.f;
    float startY = 400.f;
    float buttonWidth = 400.f;
    float buttonHeight = 80.f;
    float buttonSpacing = 100.f;
    
    // Définir les boutons
    std::vector<std::pair<std::string, MenuAction>> buttonData = {
        {"PLAY", MenuAction::Level},
        {"HELP", MenuAction::Help},
        {"VOLUME +", MenuAction::VolumeUp},
        {"VOLUME -", MenuAction::VolumeDown},
        {"LEVEL", MenuAction::Level}
    };
    
    for (size_t i = 0; i < buttonData.size(); ++i) {
        MenuButton button;
        
        // Configuration du rectangle du bouton
        button.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        button.shape.setFillColor(buttonColor);
        button.shape.setOutlineColor(sf::Color::White);
        button.shape.setOutlineThickness(3.f);
        
        // Position du bouton
        float posY = startY + i * buttonSpacing;
        button.shape.setPosition(centerX - buttonWidth / 2.f, posY);
        
        // Configuration du texte du bouton
        button.text.setFont(font);
        button.text.setString(buttonData[i].first);
        button.text.setCharacterSize(40);
        button.text.setFillColor(buttonTextColor);
        button.text.setStyle(sf::Text::Bold);
        
        // Centrer le texte dans le bouton
        sf::FloatRect textBounds = button.text.getLocalBounds();
        button.text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        button.text.setPosition(centerX, posY + buttonHeight / 2.f);
        
        // Action du bouton
        button.action = buttonData[i].second;
        
        // Zone cliquable
        button.clickZone = sf::FloatRect(
            centerX - buttonWidth / 2.f,
            posY,
            buttonWidth,
            buttonHeight
        );
        
        buttons.push_back(button);
    }
}

void MainMenu::draw(sf::RenderWindow &window) {
    // Fond dégradé (simulé avec une couleur unie pour l'instant)
    window.clear(sf::Color(25, 25, 35)); // Bleu foncé
    
    // Dessiner le titre
    if (fontLoaded) {
        window.draw(titleText);
    }
    
    // Dessiner les boutons
    for (const auto &button : buttons) {
        window.draw(button.shape);
        if (fontLoaded) {
            window.draw(button.text);
        }
    }
}

MenuAction MainMenu::handleClick(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    
    for (const auto &button : buttons) {
        if (button.clickZone.contains(mousePos)) {
            std::cout << "Bouton cliqué: " << button.text.getString().toAnsiString() << std::endl;
            return button.action;
        }
    }
    
    return MenuAction::None;
}

void MainMenu::handleMouseMove(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    
    // Effet de survol sur les boutons
    for (auto &button : buttons) {
        if (button.clickZone.contains(mousePos)) {
            button.shape.setFillColor(buttonHoverColor);
        } else {
            button.shape.setFillColor(buttonColor);
        }
    }
}
