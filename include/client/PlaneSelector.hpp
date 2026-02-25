#ifndef PLANESELECTOR_HPP
#define PLANESELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct PlaneOption {
    std::string texturePath;
    std::string displayName;
    sf::Sprite sprite;
    sf::FloatRect clickZone;
};

class PlaneSelector {
public:
    PlaneSelector();
    
    void draw(sf::RenderWindow &window);
    void update(float mouseX, float mouseY);
    bool handleClick(float mouseX, float mouseY, std::string &selectedPlane);
    
private:
    // Textures doivent être stockées séparément pour garantir leur durée de vie
    sf::Texture plane1Texture;
    sf::Texture plane2Texture;
    sf::Texture plane3Texture;
    sf::Texture plane4Texture;
    sf::Texture plane5Texture;
    sf::Texture choosePlaneTexture;
    
    // Sprites
    sf::Sprite choosePlaneSprite;
    
    // Texte d'accueil
    sf::Font font;
    sf::Text welcomeText;
    sf::Text instructionText;
    bool fontLoaded;
    
    std::vector<PlaneOption> planes;
    
    void setupPlanes();
    void setupText();
};

#endif // PLANESELECTOR_HPP

