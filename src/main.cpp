#include "raylib.h"

int main() {
    InitWindow(800, 600, "Raylib Test - ParticleFluids");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("Raylib is working.", 280, 250, 30, LIGHTGRAY);
        DrawCircle(400, 350, 50, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}