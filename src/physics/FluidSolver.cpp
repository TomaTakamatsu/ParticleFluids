#include "physics/FluidSolver.h"
#include <cmath>

FluidSolver::FluidSolver(float w, float h) : width(w), height(h) {}

void FluidSolver::Update(float dt) {
}

void FluidSolver::SpawnParticlesGrid(int count) {
    particles.reserve(count);

    int particlesPerRow = (int)std::sqrt(count);
    int particlesPerCol = (count - 1) / particlesPerRow + 1;
    
    float spacing = particleRadius * 2.0f + 1.0f; 

    float startX = width / 2.0f - (particlesPerRow * spacing) / 2.0f;
    float startY = height / 2.0f - (particlesPerCol * spacing) / 2.0f;

    for (int i = 0; i < count; i++) {
        float x = startX + (i % particlesPerRow) * spacing;
        float y = startY + (i / particlesPerRow) * spacing;

        particles.emplace_back(x, y); 
    }
}

void FluidSolver::SpawnParticlesRandom(int count) {
}