#ifndef WINMENU_HPP
#define WINMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Les actions possibles depuis cet écran
enum class WinAction {
    None,
    Retry,      // Recommencer le niveau
    Continue,   // Passer au niveau suivant (ou relancer pour l'instant)
    MainMenu    // Revenir au menu principal
};

struct WinButton {
    sf::RectangleShape shape;
    sf::Text text;
    sf::FloatRect clickZone;
    WinAction action;
};

class WinMenu {
public:
    WinMenu();

    void draw(sf::RenderWindow &window);
    WinAction handleClick(float mouseX, float mouseY);
    void handleMouseMove(float mouseX, float mouseY);

private:
    sf::Font font;
    sf::Text titleText;
    std::vector<WinButton> buttons;

    void setupButtons();
};

#endif // WINMENU_HPP
