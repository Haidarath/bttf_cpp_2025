#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "client/MainMenu.hpp" // For MenuAction

class SettingsMenu {
public:
    SettingsMenu();
    
    void draw(sf::RenderWindow &window);
    MenuAction handleClick(float mouseX, float mouseY);
    void handleMouseMove(float mouseX, float mouseY);
    
private:
    sf::Font font;
    bool fontLoaded;
    
    sf::Text titleText;
    
    // Boutons de réglage
    struct SettingsButton {
        sf::RectangleShape shape;
        sf::Text text;
        MenuAction action;
        sf::FloatRect clickZone;
    };
    
    std::vector<SettingsButton> buttons;
    
    // Bouton Retour
    SettingsButton backButton;
    
    sf::Color buttonColor;
    sf::Color buttonHoverColor;
    sf::Color buttonTextColor;

    void setupFont();
    void setupButtons();
};

#endif // SETTINGSMENU_HPP
