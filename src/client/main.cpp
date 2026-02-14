#include <SFML/Graphics.hpp>

int main()
{
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "BTTF Shooter");

    // Boucle principale du jeu
    while (window.isOpen())
    {
        sf::Event event;

        // Gestion des événements
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Nettoyer l'écran (noir)
        window.clear();

        // Dessiner ici plus tard

        // Afficher à l'écran
        window.display();
    }

    return 0;
}
