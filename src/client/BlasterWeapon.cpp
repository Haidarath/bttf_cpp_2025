#include "client/BlasterWeapon.hpp"
#include <cmath>

BlasterWeapon::BlasterWeapon(std::vector<std::unique_ptr<Bullet>>& bulletsRef)
    : Weapon("Blaster", 30, 0.2f), bullets(bulletsRef) {
    reloadTime = 1.0f;
}

bool BlasterWeapon::fire(sf::Vector2f pos, float angle, bool isPoweredUp) {
    if (!canFire()) return false;

    float rad = angle * 3.14159f / 180.f;
    float offset = 50.f; 
    pos.x += std::cos(rad) * offset;
    pos.y += std::sin(rad) * offset;

    if (isPoweredUp && powerTexture) {
        bullets.push_back(std::make_unique<Bullet>(pos.x, pos.y, angle, 1200.f, *powerTexture));
    } else {
        bullets.push_back(std::make_unique<Bullet>(pos.x, pos.y, angle, 800.f));
    }
    
    currentAmmo--;
    fireClock.restart();
    return true;
}
