// main.cpp
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "window.h"
#include "joystick.h"
#include "level.h"

using namespace std;

// === CONFIGURACIÓN DE DEBUG ===
const bool DEBUG = false; // ← Cambia a false para producción

int main() {
    
    Color bgcolor {0,0,0,0};
    // === WINDOW ===
    Window window;
    Joystick joystick;
   
    InitWindow(window.WINDOW_WIDTH, window.WINDOW_HEIGHT, "Beats");
    ToggleFullscreen();

    // === JOYSTICK PARA MÓVILES (Y DEBUG EN PC) ===
  
    

    // === PLAYER ===
    Player player(window.WINDOW_WIDTH, window.WINDOW_HEIGHT);
Level level;
level.LoadFromFile("level1.txt");

// Posicionar al jugador donde el nivel lo indica
player.position = level.GetPlayerStartPosition();

    // === GAME LOOP ===
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // --- INPUT ---
        Vector2 inputDir = {0, 0};

        // Detectar si estamos en móvil o en modo DEBUG
        bool useJoystick = DEBUG
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_IOS)
        || true
#endif
            ;

    
            switch (window.state) {
                case 0:

                break;
                case 1:
                    if (useJoystick) {
            int touchCount = GetTouchPointCount();
            if (touchCount > 0) {
                Vector2 touchPos = GetTouchPosition(0);

                if (!joystick.isJoystickActive) {
                    if (CheckCollisionPointCircle(touchPos, joystick.joystickCenter, joystick.joystickRadiusOuter * 1.5f)) {
                        joystick.isJoystickActive = true;
                        joystick.touchStartPos = touchPos;
                        joystick.stickPos = joystick.joystickCenter;
                    }
                }

                if (joystick.isJoystickActive) {
                    Vector2 delta = Vector2Subtract(touchPos, joystick.joystickCenter);
                    float distance = Vector2Length(delta);

                    if (distance > joystick.joystickRadiusOuter) {
                        delta = Vector2Scale(Vector2Normalize(delta), joystick.joystickRadiusOuter);
                    }

                    joystick.stickPos = Vector2Add(joystick.joystickCenter, delta);
                    joystick.joystickDir = (distance > 10.0f) ? Vector2Normalize(delta) : Vector2Zero();
                }
            } else {
                joystick.isJoystickActive = false;
                joystick.stickPos = joystick.joystickCenter;
                joystick.joystickDir = Vector2Zero();
            }
            inputDir = joystick.joystickDir;
        } else {
            // PC: usar teclado
            inputDir = {
                (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
                (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
            };

        }
               bool dashPressed = IsKeyPressed(KEY_P);
        bool dashReleased = IsKeyReleased(KEY_P);

        // --- UPDATE PLAYER ---
        player.Update(deltaTime, inputDir, dashPressed, dashReleased);
        player.Update(deltaTime, inputDir, dashPressed, dashReleased);
level.Update(deltaTime, player);

                break;
            }
 
        // --- DRAW ---
        BeginDrawing();
        ClearBackground(bgcolor);

        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);


        switch (window.state) {
            case 0:

            break;

        case 1:
          if (player.ShouldSpawnRing() || player.IsOnCooldown()) {
            if (player.ShouldSpawnRing()) {
                player.ResetRingFlag();
            }

            float t = player.GetCooldownProgress();
            float ringProgress = t; // Fixed: was always 0
            float maxRadius = 60.0f;
            float innerRadius = ringProgress * (maxRadius - 9.0f);
            float outerRadius = ringProgress * maxRadius;
            
            DrawRing(
                player.GetDashStartPos(),
                innerRadius,
                outerRadius,
                0, 360,
                32,
                (Color){0, 255, 244, (unsigned char)(255 * (1.0f - t))} // Fade out
            );
        }
        // Draw player
        level.Draw();

        player.Draw();

        DrawRectangle(0, 0, 300, 300, Color {255, 32, 114, 255});

        // 🕹️ DIBUJAR JOYSTICK si estamos en móvil o en modo DEBUG
        if (useJoystick) {
            DrawRing(joystick.joystickCenter, joystick.joystickRadiusOuter - 12, joystick.joystickRadiusOuter, 0, 360, 32, (Color){255, 255, 255, 80});
            DrawCircle(joystick.stickPos.x, joystick.stickPos.y, joystick.joystickRadiusInner, (Color){255, 255, 255, 200});
            DrawCircle(joystick.joystickCenter.x, joystick.joystickCenter.y, 8, (Color){0, 255, 244, 200});
        }

        break;
        
        }
        // ✨ SMOOTH RING ANIMATION ✨
      

        EndDrawing();
    }

    CloseWindow();
    return 0;
}