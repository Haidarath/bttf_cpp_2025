#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include "client/Player.hpp"
#include "client/Background.hpp"

class Level {
public:
    Level(const std::string &bgTexture, const std::string &playerTexture);
    
    void update();
    void draw(sf::RenderWindow &window);

private:
    Background background;
    Player player;
    sf::Text Niveau1Text;
    sf::Font font;
    bool fontLoaded;
};

#endif // LEVEL_HPP
