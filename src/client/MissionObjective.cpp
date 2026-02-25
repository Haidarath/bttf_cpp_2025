#include "client/MissionObjective.hpp"
#include <iomanip>
#include <sstream>

MissionObjective::MissionObjective(int targetScore, float timeLimit)
    : targetScore(targetScore), currentScore(0), timeLimit(timeLimit), remainingTime(timeLimit)
{
    fontLoaded = false;
    if (font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Black.ttf")) {
        fontLoaded = true;
    }

    if (fontLoaded) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(1600.f, 20.f);

        timerText.setFont(font);
        timerText.setCharacterSize(30);
        timerText.setFillColor(sf::Color::Yellow);
        timerText.setPosition(1600.f, 60.f);
    }
}

void MissionObjective::update(float deltaTime) {
    if (remainingTime > 0 && !isCompleted()) {
        remainingTime -= deltaTime;
        if (remainingTime < 0) remainingTime = 0;
    }

    if (fontLoaded) {
        scoreText.setString("SCORE: " + std::to_string(currentScore) + " / " + std::to_string(targetScore));
        
        std::stringstream ss;
        ss << "TEMPS: " << std::fixed << std::setprecision(1) << remainingTime << "s";
        timerText.setString(ss.str());
        
        if (remainingTime < 10.0f) {
            timerText.setFillColor(sf::Color::Red);
        }
    }
}

void MissionObjective::addScore(int points) {
    currentScore += points;
}

bool MissionObjective::isFailed() const {
    return remainingTime <= 0 && currentScore < targetScore;
}

bool MissionObjective::isCompleted() const {
    return currentScore >= targetScore;
}

void MissionObjective::draw(sf::RenderWindow &window) {
    if (fontLoaded) {
        window.draw(scoreText);
        window.draw(timerText);
    }
}
