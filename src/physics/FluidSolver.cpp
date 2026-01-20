#include "physics/FluidSolver.h"
#include <cmath>

FluidSolver::FluidSolver(float w, float h) : width(w), height(h) {}

void FluidSolver::Update(float dt)
{
    for (auto& p : particles)
    {
        p.velocity.y += gravity * dt;
        p.position += p.velocity * dt;

        p.predictedPosition = p.position;
    }

    ResolveCollisions();
}

void FluidSolver::SpawnParticlesGrid(int count)
{
    particles.reserve(count);

    int particlesPerRow = (int)std::sqrt(count);
    int particlesPerCol = (count - 1) / particlesPerRow + 1;
    
    float spacing = particleRadius * 2.0f + 1.0f; 

    float startX = width / 2.0f - (particlesPerRow * spacing) / 2.0f;
    float startY = height / 2.0f - (particlesPerCol * spacing) / 2.0f;

    for (int i = 0; i < count; i++)
    {
        float x = startX + (i % particlesPerRow) * spacing;
        float y = startY + (i / particlesPerRow) * spacing;

        particles.emplace_back(x, y); 
    }
}

void FluidSolver::SpawnParticlesRandom(int count)
{
}

void FluidSolver::ResolveCollisions()
{
    for (auto& p : particles)
    {
        if (p.position.x < 0 + particleRadius)
        {
            p.position.x = particleRadius;
            p.velocity.x *= -1 * collisionDamper;
        }
        else if (p.position.x > width - particleRadius)
        {
            p.position.x = width - particleRadius;
            p.velocity.x *= -1 * collisionDamper;
        }

        if (p.position.y < 0 + particleRadius)
        {
            p.position.y = particleRadius;
            p.velocity.y *= -1 * collisionDamper;
        }
        else if (p.position.y > height - particleRadius)
        {
            p.position.y = height - particleRadius;
            p.velocity.y *= -1 * collisionDamper;
        }
    }
}