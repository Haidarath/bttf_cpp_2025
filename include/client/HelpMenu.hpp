#ifndef HELPMENU_HPP
#define HELPMENU_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class HelpMenu {
public:
    HelpMenu();
    
    void draw(sf::RenderWindow &window);
    bool handleClick(float mouseX, float mouseY); // Retourne true si on clique sur "Retour"
    void handleMouseMove(float mouseX, float mouseY);
    
private:
    sf::Font font;
    bool fontLoaded;
    
    sf::Text titleText;
    std::vector<sf::Text> helpLines;
    
    // Bouton Retour
    sf::RectangleShape backButton;
    sf::Text backText;
    sf::FloatRect backClickZone;
    
    sf::Color buttonColor;
    sf::Color buttonHoverColor;

    void setupFont();
    void setupContent();
};

#endif // HELPMENU_HPP
