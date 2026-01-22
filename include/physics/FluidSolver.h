#pragma once
#include <vector>
#include "physics/Particle.h"

class FluidSolver
{
public:
    std::vector<Particle> particles;

    float gravity = 0.0f;
    float smoothingRadius = 15.0f;
    float targetDensity = 0.0001f;
    float pressureMultiplier = 500000.0f;
    float collisionDamper = 0.5f;
    
    float particleCount = 1000.0f;
    float particleRadius = 3.0f;
    float particleMass = 10.0f;

    float width;
    float height;

    FluidSolver(float w, float h);

    void SpawnParticlesGrid(int count);
    void SpawnParticlesRandom(int count);

    void Update(float dt);

private:
    void CalculateDensities();
    void CalculatePressureForces();
    void Integrate(float dt);
    void ResolveCollisions();

    float SmoothingKernel(float dist);
    float SmoothingKernelDerivative(float dist);
    float DensityToPressure(float density);
    
    Vec2 GetRandomDirection();
};