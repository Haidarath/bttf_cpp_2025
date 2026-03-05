#ifndef GRAVITYLAUNCHERWEAPON_HPP
#define GRAVITYLAUNCHERWEAPON_HPP

#include "client/Weapon.hpp"
#include "client/GravityBubble.hpp"
#include <memory>

class GravityLauncherWeapon : public Weapon {
public:
    GravityLauncherWeapon(std::unique_ptr<GravityBubble>& bubbleRef);
    bool fire(sf::Vector2f pos, float angle, bool isPoweredUp = false) override;
    void reload() override;

private:
    std::unique_ptr<GravityBubble>& bubble;
};

#endif // GRAVITYLAUNCHERWEAPON_HPP
