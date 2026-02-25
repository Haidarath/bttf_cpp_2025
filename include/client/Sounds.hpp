#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class Sounds {
public:
    static Sounds& getInstance();

    void playSound(const std::string& name);
    void playMusic(const std::string& name, bool loop = true);
    void stopMusic();
    
    void setVolume(float volume); // 0.0f à 100.0f
    float getVolume() const;
    void adjustVolume(float delta);

private:
    Sounds();
    ~Sounds() = default;

    // Désactiver la copie
    Sounds(const Sounds&) = delete;
    Sounds& operator=(const Sounds&) = delete;

    std::map<std::string, sf::SoundBuffer> buffers;
    sf::Sound sound;
    sf::Music music;

    void loadSound(const std::string& name, const std::string& path);
};

#endif // SOUNDS_HPP
