#ifndef BLASTERWEAPON_HPP
#define BLASTERWEAPON_HPP

#include "client/Weapon.hpp"
#include "client/Bullet.hpp"
#include <vector>
#include <memory>

class BlasterWeapon : public Weapon {
public:
    BlasterWeapon(std::vector<std::unique_ptr<Bullet>>& bulletsRef);
    bool fire(sf::Vector2f pos, float angle, bool isPoweredUp = false) override;
    void setPowerTexture(const sf::Texture& tex) override { powerTexture = &tex; }

private:
    std::vector<std::unique_ptr<Bullet>>& bullets;
    const sf::Texture* powerTexture = nullptr;
};

#endif // BLASTERWEAPON_HPP
