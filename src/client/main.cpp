#include <SFML/Graphics.hpp>
#include "client/Level.hpp"
#include "client/Background.hpp"
#include "client/PlaneSelector.hpp"
#include <iostream>
#include <memory>

enum class GameState {
    Map,
    PlaneSelection,
    Level1
};

int main()
{
    std::cout << "Starting application..." << std::endl;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BTTF Shooter", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    GameState currentState = GameState::Map;
    sf::Clock heartbeatClock;

    try {
        std::cout << "Loading map background..." << std::endl;
        Background mapBackground("sprites/background.png"); 
        std::unique_ptr<Level> currentLevel = nullptr;
        std::unique_ptr<PlaneSelector> planeSelector = nullptr;
        std::string selectedPlaneTexture = "";

        std::cout << "Entering main loop..." << std::endl;
        while (window.isOpen())
        {
            // Log périodique pour vérifier que le programme tourne toujours
            if (heartbeatClock.getElapsedTime().asSeconds() > 2.0f) {
                std::cout << "Heartbeat: Application is running..." << std::endl;
                heartbeatClock.restart();
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    std::cout << "Window close event detected." << std::endl;
                    window.close();
                }
                
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Conversion des coordonnées pixels en coordonnées monde (vue)
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        
                        std::cout << "Clic detected at: X=" << mousePos.x << ", Y=" << mousePos.y << std::endl;

                        if (currentState == GameState::Map) {
                            // Clic sur la carte -> afficher le menu de sélection d'avion
                            currentState = GameState::PlaneSelection;
                            planeSelector = std::make_unique<PlaneSelector>();
                            std::cout << "Switching to PlaneSelection!" << std::endl;
                        }
                        else if (currentState == GameState::PlaneSelection && planeSelector) {
                            // Clic sur le menu de sélection -> vérifier si un avion est cliqué
                            if (planeSelector->handleClick(mousePos.x, mousePos.y, selectedPlaneTexture)) {
                                currentState = GameState::Level1;
                                currentLevel = std::make_unique<Level>("sprites/background.png", selectedPlaneTexture);
                                std::cout << "Switching to Level1 with " << selectedPlaneTexture << "!" << std::endl;
                            }
                        }
                    }
                }
            }

            // Update
            if (currentState == GameState::Level1 && currentLevel) {
                currentLevel->update();
            }

            // Draw
            window.clear(sf::Color::Black); // Fond noir par défaut si rien n'est dessiné
            
            if (currentState == GameState::Map) {
                mapBackground.draw(window);
            }
            else if (currentState == GameState::PlaneSelection && planeSelector) {
                planeSelector->draw(window);
            }
            else if (currentState == GameState::Level1 && currentLevel) {
                currentLevel->draw(window);
            }

            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Application closed normally." << std::endl;
    return 0;
}
