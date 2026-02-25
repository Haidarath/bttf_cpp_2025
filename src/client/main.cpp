#include <SFML/Graphics.hpp>
#include "client/Level.hpp"
#include "client/Background.hpp"
#include "client/PlaneSelector.hpp"
#include "client/MainMenu.hpp"
#include "client/GameOverMenu.hpp"
#include "client/WinMenu.hpp"
#include "client/HelpMenu.hpp"
#include "client/Sounds.hpp"
#include <iostream>
#include <memory>

enum class GameState {
    MainMenu,
    Map,
    PlaneSelection,
    Level1,
    GameOver,
    Win,
    Help
};

int main()
{
    std::cout << "Starting application..." << std::endl;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BTTF Shooter", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    GameState currentState = GameState::MainMenu;
    sf::Clock heartbeatClock;
    sf::Clock deltaClock;

    Sounds::getInstance().playMusic("MENU");

    try {
        std::cout << "Loading main menu..." << std::endl;
        std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>();
        std::unique_ptr<Background> mapBackground = nullptr;
        std::unique_ptr<Level> currentLevel = nullptr;
        std::unique_ptr<PlaneSelector> planeSelector = nullptr;
        std::unique_ptr<GameOverMenu> gameOverMenu = nullptr; 
        std::unique_ptr<WinMenu> winMenu = nullptr; 
        std::unique_ptr<HelpMenu> helpMenu = nullptr;
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
                
                if (event.type == sf::Event::MouseMoved) {
                    if (currentState == GameState::MainMenu && mainMenu) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        mainMenu->handleMouseMove(mousePos.x, mousePos.y);
                    } else if (currentState == GameState::GameOver && gameOverMenu) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        gameOverMenu->handleMouseMove(mousePos.x, mousePos.y);
                    } else if (currentState == GameState::Win && winMenu) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        winMenu->handleMouseMove(mousePos.x, mousePos.y);
                    } else if (currentState == GameState::Help && helpMenu) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        helpMenu->handleMouseMove(mousePos.x, mousePos.y);
                    } else if (currentState == GameState::PlaneSelection && planeSelector) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        planeSelector->update(mousePos.x, mousePos.y);
                    }
                }
                
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Conversion des coordonnées pixels en coordonnées monde (vue)
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        
                        std::cout << "Clic detected at: X=" << mousePos.x << ", Y=" << mousePos.y << std::endl;

                        if (currentState == GameState::MainMenu && mainMenu) {
                            // Clic sur le menu principal
                            MenuAction action = mainMenu->handleClick(mousePos.x, mousePos.y);
                            
                            if (action != MenuAction::None) {
                                if (action == MenuAction::Help) Sounds::getInstance().playSound("HELP");
                                else if (action == MenuAction::VolumeUp) Sounds::getInstance().adjustVolume(10.f);
                                else if (action == MenuAction::VolumeDown) Sounds::getInstance().adjustVolume(-10.f);
                                else Sounds::getInstance().playSound("PLAY");
                            }

                            if (action == MenuAction::Play || action == MenuAction::Level) {
                                currentState = GameState::Map;
                                mapBackground = std::make_unique<Background>("sprites/background/sol1.jpg", 0.f, 0.f, false);
                                Sounds::getInstance().stopMusic();
                                Sounds::getInstance().playMusic("LEVEL");
                                std::cout << "Switching to Map from " << (action == MenuAction::Play ? "PLAY" : "LEVEL") << "!" << std::endl;
                            } else if (action == MenuAction::Help) {
                                currentState = GameState::Help;
                                helpMenu = std::make_unique<HelpMenu>();
                                std::cout << "Switching to Help!" << std::endl;
                            }
                        }
                        else if (currentState == GameState::Map) {
                            // Clic sur la carte -> afficher le menu de sélection d'avion
                            currentState = GameState::PlaneSelection;
                            planeSelector = std::make_unique<PlaneSelector>();
                            std::cout << "Switching to PlaneSelection!" << std::endl;
                        }
                        else if (currentState == GameState::PlaneSelection && planeSelector) {
                            // Clic sur le menu de sélection -> vérifier si un avion est cliqué
                            if (planeSelector->handleClick(mousePos.x, mousePos.y, selectedPlaneTexture)) {
                                currentState = GameState::Level1;
                                // On peut imaginer choisir le niveau ici, pour l'instant Niveau 1
                                currentLevel = std::make_unique<Level>("sprites/background/sol1.jpg", selectedPlaneTexture, 1);
                                Sounds::getInstance().playSound("PLAY");
                                std::cout << "Switching to Level 1 with " << selectedPlaneTexture << "!" << std::endl;
                            }
                        }
                        else if (currentState == GameState::GameOver && gameOverMenu) {
                            // Clic sur l'écran Game Over
                            GameOverAction action = gameOverMenu->handleClick(mousePos.x, mousePos.y);
                            if (action == GameOverAction::Retry) {
                                Sounds::getInstance().playSound("PLAY");
                                // On recommence le niveau
                                currentLevel = std::make_unique<Level>("sprites/background/sol1.jpg", selectedPlaneTexture, 1);
                                currentState = GameState::Level1;
                                Sounds::getInstance().playMusic("LEVEL");
                            } else if (action == GameOverAction::MainMenu) {
                                Sounds::getInstance().playSound("BACK");
                                currentState = GameState::MainMenu;
                                Sounds::getInstance().playMusic("MENU");
                            }
                        }
                        else if (currentState == GameState::Win && winMenu) {
                            WinAction action = winMenu->handleClick(mousePos.x, mousePos.y);
                            if (action == WinAction::Continue || action == WinAction::Retry) {
                                Sounds::getInstance().playSound("PLAY");
                                currentLevel = std::make_unique<Level>("sprites/background/sol1.jpg", selectedPlaneTexture, 1);
                                currentState = GameState::Level1;
                                Sounds::getInstance().playMusic("LEVEL");
                            } else if (action == WinAction::MainMenu) {
                                Sounds::getInstance().playSound("BACK");
                                currentState = GameState::MainMenu;
                                Sounds::getInstance().playMusic("MENU");
                            }
                        }
                        else if (currentState == GameState::Help && helpMenu) {
                            if (helpMenu->handleClick(mousePos.x, mousePos.y)) {
                                Sounds::getInstance().playSound("BACK");
                                currentState = GameState::MainMenu;
                            }
                        }
                    }
                }
            }

            // Update
            float deltaTime = deltaClock.restart().asSeconds();
            if (currentState == GameState::Level1 && currentLevel) {
                currentLevel->update(deltaTime, window);
                
                // Si le joueur est mort, on passe en Game Over
                if (currentLevel->isGameOver()) {
                    currentState = GameState::GameOver;
                    gameOverMenu = std::make_unique<GameOverMenu>();
                    Sounds::getInstance().stopMusic();
                    Sounds::getInstance().playSound("LOSE");
                } else if (currentLevel->isLevelComplete()) {
                    currentState = GameState::Win;
                    winMenu = std::make_unique<WinMenu>();
                    Sounds::getInstance().stopMusic();
                    Sounds::getInstance().playSound("WIN");
                }
            }

            // Draw
            window.clear(sf::Color::Black); // Fond noir par défaut si rien n'est dessiné
            
            if (currentState == GameState::MainMenu && mainMenu) {
                mainMenu->draw(window);
            }
            else if (currentState == GameState::Map && mapBackground) {
                mapBackground->draw(window);
            }
            else if (currentState == GameState::PlaneSelection && planeSelector) {
                planeSelector->draw(window);
            }
            else if (currentState == GameState::Level1 && currentLevel) {
                currentLevel->draw(window);
            }
            else if (currentState == GameState::GameOver && gameOverMenu) {
                // On dessine le niveau en fond, et le menu Game Over par dessus
                if (currentLevel) currentLevel->draw(window);
                gameOverMenu->draw(window);
            }
            else if (currentState == GameState::Win && winMenu) {
                if (currentLevel) currentLevel->draw(window);
                winMenu->draw(window);
            }
            else if (currentState == GameState::Help && helpMenu) {
                helpMenu->draw(window);
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
