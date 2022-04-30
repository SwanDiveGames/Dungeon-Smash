#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "baseCharacter.h"
#include "character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D running_texture, int frameCount, float scale); // class constructor
    virtual void tick(float deltaTime) override;                                                      // Update function
    void setTarget(Character *character){target = character;}                                         // Set character as a target
    virtual Vector2 getScreenPos() override;

private:
    Character *target;
    float damagePerSec{10.f};
    float radius{25.f};
};

#endif