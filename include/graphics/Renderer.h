#pragma once
#include "physics/FluidSolver.h"

class Renderer
{
public:
    Renderer(FluidSolver& solver);

    void Render();

private:
    FluidSolver& solver;
};