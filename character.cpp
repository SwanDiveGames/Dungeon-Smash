#include "character.h"
#include "raymath.h"

Character::Character(int gameWidth, int gameHeight, int frameCount, float gameScale) : screenWidth(gameWidth),
                                                                                       screenHeight(gameHeight)
{
    scale = gameScale;
    maxFrames = frameCount;
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2
    {
        static_cast<float>(screenWidth) / 2.0f - scale *(0.5f * width),
        static_cast<float>(screenHeight) / 2.0f - scale *(0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    // Detect key presses

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;

    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;

    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;

    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if (facing > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {80.f, 110.f};
        weaponCollisionRect = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };

        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {45.f, 110.f};
        weaponCollisionRect = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };

        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    //Draw Sword
    Rectangle source {0.f, 0.f, static_cast<float>(weapon.width) * facing, static_cast<float>(weapon.height)};
    Rectangle dest {getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}
