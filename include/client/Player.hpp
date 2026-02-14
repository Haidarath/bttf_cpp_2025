#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    Player(const std::string &textureFile, float x, float y);

    void update();              // Pour d'éventuels futurs comportements
    void handleInput();         // Gère les entrées clavier pour le mouvement
    void move(float dx, float dy); // Déplace le joueur
    void setScale(float factor);   // Ajuste la taille
    void draw(sf::RenderWindow &window); // Dessine le joueur

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // PLAYER_HPP
