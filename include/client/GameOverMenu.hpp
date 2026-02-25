#ifndef GAMEOVERMENU_HPP
#define GAMEOVERMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Les actions possibles depuis cet écran
enum class GameOverAction {
    None,
    Retry,      // Recommencer le niveau
    MainMenu    // Revenir au menu principal
};

struct GameOverButton {
    sf::RectangleShape shape;
    sf::Text text;
    sf::FloatRect clickZone;
    GameOverAction action;
};

class GameOverMenu {
public:
    GameOverMenu();

    void draw(sf::RenderWindow &window);
    GameOverAction handleClick(float mouseX, float mouseY);
    void handleMouseMove(float mouseX, float mouseY);

private:
    sf::Font font;
    sf::Text titleText;
    std::vector<GameOverButton> buttons;

    void setupButtons();
};

#endif // GAMEOVERMENU_HPP
