#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class MenuAction {
    None,
    Play,
    Help,
    Settings,
    Exit,
    VolumeUp,
    VolumeDown,
    Level,
    ToggleFullscreen
};

struct MenuButton {
    sf::RectangleShape shape;
    sf::Text text;
    MenuAction action;
    sf::FloatRect clickZone;
};

class MainMenu {
public:
    MainMenu();
    
    void draw(sf::RenderWindow &window);
    MenuAction handleClick(float mouseX, float mouseY);
    void handleMouseMove(float mouseX, float mouseY);
    
private:
    // Police pour le texte
    sf::Font font;
    bool fontLoaded;
    
    // Titre du jeu
    sf::Text titleText;
    
    // Boutons du menu
    std::vector<MenuButton> buttons;
    
    // Couleurs
    sf::Color buttonColor;
    sf::Color buttonHoverColor;
    sf::Color buttonTextColor;
    
    void setupFont();
    void setupTitle();
    void setupButtons();
};

#endif // MAINMENU_HPP
