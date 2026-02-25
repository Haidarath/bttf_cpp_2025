#include "client/Sounds.hpp"
#include <iostream>

Sounds& Sounds::getInstance() {
    static Sounds instance;
    return instance;
}

Sounds::Sounds() {
    // Chargement des sons des boutons et actions
    loadSound("PLAY", "sprites/sounds/click_general.mp3");
    loadSound("HELP", "sprites/sounds/click_help.wav");
    loadSound("BEST SCORE", "sprites/sounds/click_bestscore.mp3");
    loadSound("LEVEL", "sprites/sounds/click_general.mp3");
    loadSound("BACK", "sprites/sounds/click_back.mp3");
    loadSound("CONTINUE", "sprites/sounds/click_continue.mp3");
    
    loadSound("SHOOT", "sprites/music/laser_shot.wav");
    loadSound("EXPLOSION", "sprites/music/enemy_destroyed.wav");
    loadSound("HIT", "sprites/music/player_hit.mp3");
    loadSound("LOSE", "sprites/sounds/lose_sound.wav");
    loadSound("WIN", "sprites/sounds/win_sound.wav");
}

void Sounds::loadSound(const std::string& name, const std::string& path) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path)) {
        buffers[name] = buffer;
    } else {
        std::cerr << "Erreur : Impossible de charger le son : " << path << std::endl;
    }
}

void Sounds::playSound(const std::string& name) {
    if (buffers.count(name)) {
        sound.setBuffer(buffers[name]);
        sound.play();
    }
}

void Sounds::playMusic(const std::string& name, bool loop) {
    std::string path = "";
    if (name == "MENU") path = "sprites/music/retro game theme.wav";
    else if (name == "LEVEL") path = "sprites/music/8-bit background music.wav";
    else if (name == "BOSS") path = "sprites/music/bossbattle.mp3";
    
    if (path != "" && music.openFromFile(path)) {
        music.setLoop(loop);
        music.setVolume(50);
        music.play();
    }
}

void Sounds::stopMusic() {
    music.stop();
}

void Sounds::setVolume(float volume) {
    if (volume < 0.f) volume = 0.f;
    if (volume > 100.f) volume = 100.f;
    
    sound.setVolume(volume);
    music.setVolume(volume);
}

float Sounds::getVolume() const {
    return music.getVolume();
}

void Sounds::adjustVolume(float delta) {
    setVolume(getVolume() + delta);
    std::cout << "Volume adjusted to: " << getVolume() << std::endl;
}
