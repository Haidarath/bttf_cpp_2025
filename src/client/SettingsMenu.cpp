#include "client/SettingsMenu.hpp"
#include <iostream>

SettingsMenu::SettingsMenu() {
    buttonColor = sf::Color(70, 130, 180);        // Steel blue
    buttonHoverColor = sf::Color(100, 149, 237);  // Cornflower blue
    buttonTextColor = sf::Color::White;
    
    setupFont();
    setupButtons();
}

void SettingsMenu::setupFont() {
    fontLoaded = false;
    
    std::vector<std::string> fontPaths = {
        "/usr/share/fonts/truetype/noto/NotoSans-Black.ttf",
        "/usr/share/fonts/truetype/noto/NotoSans-Bold.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"
    };
    
    for (const auto& fontPath : fontPaths) {
        if (font.loadFromFile(fontPath)) {
            fontLoaded = true;
            break;
        }
    }
}

void SettingsMenu::setupButtons() {
    if (!fontLoaded) return;
    
    float centerX = 1920.f / 2.f;
    float startY = 300.f;
    float buttonWidth = 500.f;
    float buttonHeight = 80.f;
    float buttonSpacing = 120.f;
    
    titleText.setFont(font);
    titleText.setString("SETTINGS");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    titleText.setPosition(centerX, 150.f);
    
    std::vector<std::pair<std::string, MenuAction>> buttonData = {
        {"VOLUME +", MenuAction::VolumeUp},
        {"VOLUME -", MenuAction::VolumeDown},
        {"TOGGLE FULLSCREEN", MenuAction::ToggleFullscreen},
        {"BACK", MenuAction::None}
    };
    
    for (size_t i = 0; i < buttonData.size(); ++i) {
        SettingsButton button;
        
        button.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        button.shape.setFillColor(buttonColor);
        button.shape.setOutlineColor(sf::Color::White);
        button.shape.setOutlineThickness(3.f);
        
        float posY = startY + i * buttonSpacing;
        button.shape.setPosition(centerX - buttonWidth / 2.f, posY);
        
        button.text.setFont(font);
        button.text.setString(buttonData[i].first);
        button.text.setCharacterSize(40);
        button.text.setFillColor(buttonTextColor);
        button.text.setStyle(sf::Text::Bold);
        
        sf::FloatRect btnTextBounds = button.text.getLocalBounds();
        button.text.setOrigin(btnTextBounds.width / 2.f, btnTextBounds.height / 2.f);
        button.text.setPosition(centerX, posY + buttonHeight / 2.f);
        
        button.action = buttonData[i].second;
        button.clickZone = sf::FloatRect(centerX - buttonWidth / 2.f, posY, buttonWidth, buttonHeight);
        
        buttons.push_back(button);
    }
}

void SettingsMenu::draw(sf::RenderWindow &window) {
    window.clear(sf::Color(25, 25, 35));
    
    if (fontLoaded) {
        window.draw(titleText);
    }
    
    for (const auto &button : buttons) {
        window.draw(button.shape);
        if (fontLoaded) {
            window.draw(button.text);
        }
    }
}

MenuAction SettingsMenu::handleClick(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    
    for (const auto &button : buttons) {
        if (button.clickZone.contains(mousePos)) {
            // Return back if clicked BACK
            if (button.text.getString() == "BACK") {
                return MenuAction::None; // In our case it will signal to go back to MainMenu
            }
            return button.action;
        }
    }
    
    return MenuAction::Play; // Some dummy action to say nothing happened that requires going back
}

void SettingsMenu::handleMouseMove(float mouseX, float mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    
    for (auto &button : buttons) {
        if (button.clickZone.contains(mousePos)) {
            button.shape.setFillColor(buttonHoverColor);
        } else {
            button.shape.setFillColor(buttonColor);
        }
    }
}
