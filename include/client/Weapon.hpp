#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Weapon {
public:
    Weapon(const std::string& name, int maxAmmo, float fireRate);
    virtual ~Weapon() = default;

    virtual bool canFire() const;
    virtual void reload();
    virtual void update(float deltaTime);
    virtual bool fire(sf::Vector2f pos, float angle, bool isPoweredUp = false) = 0;
    virtual void setPowerTexture(const sf::Texture& tex) { (void)tex; }

    std::string getName() const;
    int getCurrentAmmo() const;
    int getMaxAmmo() const;
    bool getIsReloading() const;

protected:
    std::string name;
    int maxAmmo;
    int currentAmmo;
    float fireRate;
    sf::Clock fireClock;
    bool isReloading = false;
    sf::Clock reloadClock;
    float reloadTime;
};

#endif // WEAPON_HPP
