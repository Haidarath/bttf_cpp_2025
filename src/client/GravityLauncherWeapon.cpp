#include "client/GravityLauncherWeapon.hpp"
#include <cmath>

GravityLauncherWeapon::GravityLauncherWeapon(std::unique_ptr<GravityBubble>& bubbleRef)
    : Weapon("Gravity Launcher", 3, 5.0f), bubble(bubbleRef) {
}

void GravityLauncherWeapon::reload() {
    // Aucune recharge pour cette arme, limite de 3 par partie
}

bool GravityLauncherWeapon::fire(sf::Vector2f pos, float angle, bool isPoweredUp) {
    (void)isPoweredUp;
    // On ne tire que si aucune bulle n'est active et qu'on a des munitions
    if (!canFire() || bubble != nullptr) return false;

    float rad = angle * 3.14159f / 180.f;
    float offset = 300.f; 
    pos.x += std::cos(rad) * offset;
    pos.y += std::sin(rad) * offset;

    bubble = std::make_unique<GravityBubble>(pos.x, pos.y);
    
    currentAmmo--;
    fireClock.restart();
    return true;
}
