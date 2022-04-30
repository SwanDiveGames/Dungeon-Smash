#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "baseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int gameWidth, int gameHeight, int maxFrames, float gameScale);
    float getWidth() { return width; }                                 // Returns width of character
    float getHeight() { return height; }                               // Returns height of character
    virtual Vector2 getScreenPos() override;                           // Get screen position
    virtual void tick(float deltaTime) override;                       // Update function
    Rectangle getWeaponCollisionRect() { return weaponCollisionRect; } // Get weapon collision rectangle
    float getHealth() const { return health; }                         // Get character health
    void takeDamage(float damage);                                     // Function to take damage

private:
    int screenWidth{};                                              // Width of game screen
    int screenHeight{};                                             // Height of game screen
    Texture2D weapon{LoadTexture("characters/weapon_sword_1.png")}; // Weapon texture
    Rectangle weaponCollisionRect{};                                // Weapon collision detection rectangle
    float health{100.f};                                            // Character health
};

#endif
