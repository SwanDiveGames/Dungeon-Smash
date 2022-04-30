#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{
    // Variables

    // Screen Width and Height
    const int screenWidth{768}, screenHeight{768};
    const float gameScale{8.0f};

    // Initialise Window
    InitWindow(screenWidth, screenHeight, "Dungeon Smash");

    // Map
    Texture2D worldMap = LoadTexture("dungeon_tileset/WorldMap.png");
    Vector2 mapPos{250, 250};

    // Instantiate Character
    Character knight{screenWidth, screenHeight, int{6}, gameScale};

    // Instantiate enemies
    Enemy goblin{
        Vector2{1600, 600},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
        int{6},
        gameScale};

    Enemy slime{
        Vector2{1000.f, 1400.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        int{6},
        gameScale};

    Enemy *enemies[]{&goblin, &slime};

    bool enemiesDead{false};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    // Props
    Prop props[2]{
        Prop{Vector2{600.f, 350.f}, LoadTexture("dungeon_tileset/props_items/barrel.png"), gameScale},
        Prop{Vector2{500.f, 800.f}, LoadTexture("dungeon_tileset/props_items/table.png"), gameScale}};

    // Set Target FPS
    SetTargetFPS(60);

    // While Game is Open
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Logic Begins
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f); // moves the map in the opposite direction to the player
        mapPos.x -= gameScale * knight.getWidth() / 2;
        mapPos.y -= gameScale * knight.getHeight();

        // Draw Map
        DrawTextureEx(worldMap, mapPos, 0.0, gameScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive()) // Knight is dead
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Knight is alive
        {
            int enemiesDead{};
            for (auto enemy : enemies)
            {
                if (!enemy->getAlive())
                    enemiesDead++;
            }

            if (enemiesDead >= 2)
            {
                DrawText("You Win!", 55.f, 45.f, 40, RED);
            }

            else
            {
                std::string knightHealth{"HP: "};
                knightHealth.append(std::to_string(knight.getHealth()), 0, 3);
                DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
            }
        }

        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + screenWidth > worldMap.width * gameScale - knight.getWidth() * gameScale ||
            knight.getWorldPos().y + screenHeight > worldMap.height * gameScale - knight.getHeight() * gameScale)
        {
            knight.undoMovement();
        }

        // Check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // Enemy collisions
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // Attacking
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRect()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        // Game Logic Ends

        EndDrawing();
    }

    // Close Program
    UnloadTexture(worldMap);
    CloseWindow();
}