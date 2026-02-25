#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Background {
public:
    Background(const std::string &textureFile, float x = 0.f, float y = 0.f, bool isScrolling = false);

    void update(float deltaTime, float speed);
    void updateOffset(float offsetX, float offsetY);
    void draw(sf::RenderWindow &window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float textureOffset;
};

#endif // BACKGROUND_HPP
