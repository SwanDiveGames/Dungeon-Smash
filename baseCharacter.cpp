#include "baseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    if (!getAlive()) return;
    worldPosLastFrame = worldPos;

    // Draw textures

    // Update Animation Frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;

        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // Set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        
        // Direction
        if (velocity.x < 0.f)
        {
            facing = -1.f;
        }
        else if (velocity.x > 0.f)
        {
            facing = 1.f;
        }
        else
        {
            facing = lastFacing;
        }
        texture = running;
    }
    else
    {
        texture = idle;
    }

    velocity = {};
    lastFacing = facing; // set the last x direction the character faced

    // Draw character
    Rectangle source{frame * width, 0.f, facing * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}