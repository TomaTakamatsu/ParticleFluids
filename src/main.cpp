#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "physics/FluidSolver.h"
#include "graphics/Renderer.h"

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 350;
    const int sidebarWidth = 300;

    InitWindow(windowWidth, windowHeight, "Particle Fluid Simulator");
    SetTargetFPS(60);

    FluidSolver solver(windowWidth - sidebarWidth, windowHeight);
    Renderer renderer(solver);

    solver.SpawnParticlesGrid(solver.particleCount);

    while (!WindowShouldClose())
    {
        float dt = 1.0f / 60.0f;
        solver.Update(dt);

        renderer.Render();
    }

    CloseWindow();
    return 0;
}