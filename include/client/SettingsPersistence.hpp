#ifndef SETTINGSPERSISTENCE_HPP
#define SETTINGSPERSISTENCE_HPP

#include <string>

struct GameSettings {
    float volume = 50.0f;
    bool isFullscreen = false;
};

class SettingsPersistence {
public:
    static void save(const GameSettings& settings, const std::string& filename = "settings.txt");
    static GameSettings load(const std::string& filename = "settings.txt");
};

#endif // SETTINGSPERSISTENCE_HPP
