#include "raylib.h"
#include "physics/FluidSolver.h"
#include "graphics/Renderer.h"

int main()
{
    float screenWidth = 800;
    float screenHeight = 600;

    InitWindow((int)screenWidth, (int)screenHeight, "Particle Fluid Simulator");
    SetTargetFPS(60);

    FluidSolver solver(screenWidth, screenHeight);
    Renderer renderer(solver);

    solver.gravity = 980.0f;
    solver.collisionDamper = 0.75f;
    solver.SpawnParticlesGrid(100);

    while (!WindowShouldClose())
    {
        float dt = 1.0f / 60.0f;
        solver.Update(dt);

        renderer.Render();
    }

    CloseWindow();
    return 0;
}