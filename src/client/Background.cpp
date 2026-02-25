#include "client/Background.hpp"
#include <iostream>

Background::Background(const std::string &textureFile, float x, float y, bool isScrolling)
    : textureOffset(0.f)
{
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Impossible de charger la texture: " + textureFile);
    }

    if (isScrolling) {
        texture.setRepeated(true);
        // On définit la taille initiale du sprite pour couvrir l'écran
        sprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    }

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Background::update(float deltaTime, float speed) {
    textureOffset += speed * deltaTime;
    // On met à jour le rectangle de texture pour créer l'effet de défilement horizontal par défaut
    sprite.setTextureRect(sf::IntRect(static_cast<int>(textureOffset), 0, 1920, 1080));
}

void Background::updateOffset(float offsetX, float offsetY) {
    // Permet de faire défiler le fond en fonction de la position du joueur (Parallaxe)
    // On divise par un facteur pour que le fond bouge plus doucement
    sprite.setTextureRect(sf::IntRect(static_cast<int>(offsetX * 0.5f), static_cast<int>(offsetY * 0.5f), 1920, 1080));
}

void Background::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
