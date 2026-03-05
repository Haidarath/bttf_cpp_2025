#include "client/SettingsPersistence.hpp"
#include <fstream>
#include <iostream>

void SettingsPersistence::save(const GameSettings& settings, const std::string& filename) {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << settings.volume << "\n";
        ofs << settings.isFullscreen << "\n";
        ofs.close();
        std::cout << "Parametres sauvegardes dans " << filename << std::endl;
    }
}

GameSettings SettingsPersistence::load(const std::string& filename) {
    GameSettings settings;
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> settings.volume;
        ifs >> settings.isFullscreen;
        ifs.close();
        std::cout << "Parametres charges de " << filename << std::endl;
    } else {
        // Create default settings file if it doesn't exist
        save(settings, filename);
    }
    return settings;
}
