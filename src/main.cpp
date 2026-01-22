#include "raylib.h"
#include "physics/FluidSolver.h"
#include "graphics/Renderer.h"

int main()
{
    float screenWidth = 500;
    float screenHeight = 350;

    InitWindow((int)screenWidth, (int)screenHeight, "Particle Fluid Simulator");
    SetTargetFPS(120);

    FluidSolver solver(screenWidth, screenHeight);
    Renderer renderer(solver);

    solver.SpawnParticlesGrid(500);

    while (!WindowShouldClose())
    {
        float dt = 1.0f / 120.0f;
        solver.Update(dt);

        renderer.Render();
    }

    CloseWindow();
    return 0;
}