#include "physics/FluidSolver.h"
#include <cmath>

FluidSolver::FluidSolver(float w, float h) : width(w), height(h) {}

void FluidSolver::Update(float dt)
{
    for (auto& p : particles)
    {
        p.velocity.y += gravity * dt; 
        p.predictedPosition = p.position + p.velocity * dt;
    }

    CalculateDensities();

    for (auto& p : particles)
    {
        p.force = Vec2(0, 0);
    }
    CalculatePressureForces();

    for (auto& p : particles)
    {
        Vec2 acceleration = p.force / particleMass;
        p.velocity += acceleration * dt;         
        p.position += p.velocity * dt;
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

float FluidSolver::SmoothingKernel(float dist)
{
    if (dist >= smoothingRadius) return 0.0f;

    float volume = (3.14159f * std::pow(smoothingRadius, 4)) / 6.0f;
    return (smoothingRadius - dist) * (smoothingRadius - dist) / volume;
}

float FluidSolver::SmoothingKernelDerivative(float dist)
{
    if (dist >= smoothingRadius) return 0.0f;
    
    float scale = 12.0f / (3.14159f * std::pow(smoothingRadius, 4));
    return (smoothingRadius - dist) * scale;
}

void FluidSolver::CalculateDensities()
{
    for (auto& p : particles) {
        p.density = 0.0f;

        for (const auto& other : particles) {
            float dist = p.predictedPosition.Distance(other.predictedPosition);
            p.density += particleMass * SmoothingKernel(dist);
        }
    }
}

float FluidSolver::DensityToPressure(float density)
{
    float densityError = density - targetDensity;
    float pressure = densityError * pressureMultiplier;

    if (pressure < 0.0f) return 0.0f;
    return pressure;
}

void FluidSolver::CalculatePressureForces()
{
    for (auto& p : particles) {
        Vec2 pressureForce(0, 0);

        for (const auto& other : particles) {
            if (&p == &other) continue;

            float dist = p.predictedPosition.Distance(other.predictedPosition);
            if (dist >= smoothingRadius) continue;

            Vec2 dir;
            if (dist < 0.001f) {
                dir = Vec2((float)rand() / RAND_MAX - 0.5f, (float)rand() / RAND_MAX - 0.5f).Normalized();
            } else {
                dir = (p.predictedPosition - other.predictedPosition) / dist; 
            }

            float slope = SmoothingKernelDerivative(dist);
            float density = other.density;

            if (density < 0.01f) density = 0.01f;

            float sharedPressure = (DensityToPressure(p.density) + DensityToPressure(other.density)) / 2.0f;

            pressureForce += dir * (sharedPressure * slope * particleMass / density);
        }
        
        p.force += pressureForce;
    }
}