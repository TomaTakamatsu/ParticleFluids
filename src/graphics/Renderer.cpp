#include "graphics/Renderer.h"
#include "raylib.h"

Renderer::Renderer(FluidSolver& s) : solver(s) {}

void Renderer::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangleLines(0, 0, (int)solver.width, (int)solver.height, GREEN);

    for (const auto& p : solver.particles)
    {
        Vector2 pos = { p.position.x, p.position.y };
        DrawCircleV(pos, solver.particleRadius, BLUE);
    }


    DrawText(TextFormat("Particles: %i", solver.particles.size()), 10, 10, 20, WHITE);
    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 30, 20, GREEN);

    EndDrawing();
}