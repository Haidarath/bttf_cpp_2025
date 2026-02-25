#ifndef MISSION_OBJECTIVE_HPP
#define MISSION_OBJECTIVE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class MissionObjective {
public:
    MissionObjective(int targetScore, float timeLimit);

    void update(float deltaTime);
    void addScore(int points);
    
    bool isFailed() const;      // Vrai si le temps est écoulé et le score non atteint
    bool isCompleted() const;   // Vrai si le score est atteint
    
    void draw(sf::RenderWindow &window);

    int getCurrentScore() const { return currentScore; }
    int getTargetScore() const { return targetScore; }
    float getRemainingTime() const { return remainingTime; }

private:
    int targetScore;
    int currentScore;
    float timeLimit;
    float remainingTime;

    sf::Font font;
    sf::Text scoreText;
    sf::Text timerText;
    bool fontLoaded;
};

#endif // MISSION_OBJECTIVE_HPP
