#include "client/Level.hpp"

Level::Level(const std::string &bgTexture, const std::string &playerTexture)
    : background(bgTexture), player(playerTexture, 800.f, 600.f)
{
    // Charger la police
    fontLoaded = false;
    if (font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Black.ttf")) {
        fontLoaded = true;
    }
    
    if (fontLoaded) {
        // Texte de niveau
        Niveau1Text.setFont(font);
        Niveau1Text.setString("Niveau 1");
        Niveau1Text.setCharacterSize(80);
        Niveau1Text.setFillColor(sf::Color::White);
        Niveau1Text.setStyle(sf::Text::Bold);
        
        // Centrer le texte
        sf::FloatRect textBounds = Niveau1Text.getLocalBounds();
        Niveau1Text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        Niveau1Text.setPosition(1920.f / 2.f, 50.f);  // En haut de l'écran
    }
    player.setScale(0.2f);
}

void Level::update() {
    player.handleInput();
    player.update();
}

void Level::draw(sf::RenderWindow &window) {
    window.clear(sf::Color(144, 238, 144)); // Vert pâle/doux pour le niveau 1
    
    // Dessiner le texte si la police est chargée
    if (fontLoaded) {
        window.draw(Niveau1Text);
    }
    
    player.draw(window);
}
