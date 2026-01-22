#include "graphics/Renderer.h"
#include "raylib.h"
#include "raygui.h"

Renderer::Renderer(FluidSolver& s) : solver(s) {}

void Renderer::Render() {
    const int sidebarWidth = 300;
    const int uiMargin = 10;
    const int uiElementHeight = 20;
    const int uiSpacing = 30;

    BeginDrawing();
    ClearBackground(DARKGRAY);
    Rectangle simRect = { (float)sidebarWidth, 0, (float)solver.width, (float)solver.height };
    
    DrawRectangleRec(simRect, BLACK);
    DrawRectangleLinesEx(simRect, 2, GREEN);

    for (const auto& p : solver.particles)
    {
        Vector2 screenPos = { p.position.x + sidebarWidth, p.position.y };
        
        Color color = BLUE;
        if (p.density > solver.targetDensity) color = SKYBLUE;
        
        DrawCircleV(screenPos, solver.particleRadius, color);
    }
    
    float yCursor = 20.0f;
    float sliderWidth = sidebarWidth - (uiMargin * 2) - 70;

    DrawText("Settings", uiMargin, yCursor, 20, WHITE);
    yCursor += 40;

    GuiSliderBar((Rectangle){ uiMargin + 40, yCursor, sliderWidth, uiElementHeight }, 
        "Grav", TextFormat("%.0f", solver.gravity), &solver.gravity, 0.0f, 2000.0f);
    yCursor += uiSpacing;

    GuiSliderBar((Rectangle){ uiMargin + 40, yCursor, sliderWidth, uiElementHeight }, 
        "Rad", TextFormat("%.1f", solver.smoothingRadius), &solver.smoothingRadius, 1.0f, 100.0f);
    yCursor += uiSpacing;

    GuiSliderBar((Rectangle){ uiMargin + 40, yCursor, sliderWidth, uiElementHeight }, 
        "Press", TextFormat("%.0f", solver.pressureMultiplier), &solver.pressureMultiplier, 100.0f, 1000000.0f);
    yCursor += uiSpacing;

    GuiSliderBar((Rectangle){ uiMargin + 40, yCursor, sliderWidth, uiElementHeight }, 
        "Dens", TextFormat("%.4f", solver.targetDensity), &solver.targetDensity, 0.00001f, 0.1f);
    yCursor += uiSpacing;
    
    GuiSliderBar((Rectangle){ uiMargin + 40, yCursor, sliderWidth, uiElementHeight }, 
        "Mass", TextFormat("%.1f", solver.particleMass), &solver.particleMass, 0.1f, 50.0f);
    yCursor += uiSpacing * 2;

    GuiSliderBar((Rectangle){ uiMargin + 40, yCursor, sliderWidth, uiElementHeight }, 
        "Count", TextFormat("%.0f", solver.particleCount), &solver.particleCount, 100.0f, 2500.0f);
    yCursor += uiSpacing * 2;

    if (GuiButton((Rectangle){ uiMargin, yCursor, (float)sidebarWidth - uiMargin*2, 30 }, "Reset Particles")) {
        solver.particles.clear();
        solver.SpawnParticlesGrid(solver.particleCount);
    }

    DrawFPS(sidebarWidth + 10, 10);
    EndDrawing();
}