#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }       // Returns world position of the character
    void undoMovement();                             // undo last frame's movement when player moves out of bounds
    Rectangle getCollisionRec();                     // returns a rectangle for collisions with props and enemies
    virtual void tick(float deltaTime);              // Update function
    virtual Vector2 getScreenPos() = 0;              // Get character's screen position
    bool getAlive() { return alive; }                // Gets character's alive state
    void setAlive(bool isAlive) { alive = isAlive; } // Sets characters alive state

protected:
    // Animation Textures
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png"); // Current texture
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");    // Idling
    Texture2D running = LoadTexture("characters/knight_run_spritesheet.png");  // Moving
    float width{};
    float height{};
    float scale{};

    // Position Vectors
    Vector2 worldPos{};          // Position in the world
    Vector2 worldPosLastFrame{}; // Position in the world before the last update

    // Movement
    float facing{1.f}; // +ve = right, -ve = left
    float speed{6.0f};
    float lastFacing{1.f}; // last direction faced
    Vector2 velocity{};

    // Animation Variables
    int frame{};                  // Current frame
    float runningTime{};          // Time since last frame change
    int maxFrames{6};             // Max frames in spritesheet
    float updateTime{1.f / 12.f}; // Frames/second for animation

private:
    bool alive{true};
};

#endif