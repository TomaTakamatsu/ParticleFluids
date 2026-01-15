#pragma once
#include "core/Vec2.h"

struct Particle {
    Vec2 position;
    Vec2 predictedPosition;
    Vec2 velocity;
    Vec2 force;

    float density;
    float pressure;

    Particle(float x, float y) {
        position = Vec2(x, y);
        predictedPosition = position;
        velocity = Vec2(0, 0);
        force = Vec2(0, 0);
        density = 0;
        pressure = 0;
    }
};