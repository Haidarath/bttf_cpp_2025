#include "client/Weapon.hpp"

Weapon::Weapon(const std::string& name, int maxAmmo, float fireRate)
    : name(name), maxAmmo(maxAmmo), currentAmmo(maxAmmo), fireRate(fireRate), reloadTime(1.5f) {}

bool Weapon::canFire() const {
    return currentAmmo > 0 && fireClock.getElapsedTime().asSeconds() > fireRate && !isReloading;
}

void Weapon::reload() {
    if (currentAmmo < maxAmmo && !isReloading) {
        isReloading = true;
        reloadClock.restart();
    }
}

void Weapon::update(float deltaTime) {
    (void)deltaTime;
    if (isReloading && reloadClock.getElapsedTime().asSeconds() > reloadTime) {
        currentAmmo = maxAmmo;
        isReloading = false;
    }
}

std::string Weapon::getName() const { return name; }
int Weapon::getCurrentAmmo() const { return currentAmmo; }
int Weapon::getMaxAmmo() const { return maxAmmo; }
bool Weapon::getIsReloading() const { return isReloading; }
