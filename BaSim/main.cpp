//
//  main.cpp
//  BaSim
//
//  Created by Manuel Lera Ramirez on 22/09/16.
//  Copyright © 2016 Manuel Lera Ramirez. All rights reserved.
//
/* BaSim, the simulation that I used to start learning C++ */

// Basic Libraries
int id_master = 0;
#include <iostream>
#include <sstream>
#include <fstream>
// Graphic Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <cstdlib>
#include <cmath>

//Two functions useful for debugging
void reached()
{
    std::cout << "reached" << std::endl;
}

void reached(int i)
{
    std::cout << "reached: "<< i << std::endl;
}

// Import the objects of the simulation
#include "params.h"
#include "Object.h"
#include "Properties.h"
#include "MT.h"
#include "ball.h"
#include "ball_prop.h"
#include "mt_prop.h"
#include "Integration.h"
#include "display.h"
#include "props_maker.h"
#include "Interactions.h"
#include "Simulation.h"

Simulation sim;

// Import input file parser and ouput file writer...
#include "object_step.h"
#include "input.h"
#include "output.h"
#include "read_output.h"


int main() {
//    EulerIntegration(start, end, step_int, step_out, vals, pars);
    Parser pars;
    std::fstream fs("config.bs");
    pars.readfile(fs);
    Simulation sim2;
    sim.run_write();
    sim2.show();
//    sim.run_play();
    return 0;
}















