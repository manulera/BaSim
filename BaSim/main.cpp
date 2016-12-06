//
//  main.cpp
//  BaSim
//
//  Created by Manuel Lera Ramirez on 22/09/16.
//  Copyright © 2016 Manuel Lera Ramirez. All rights reserved.
//
/* BaSim, the simulation that I used to start learning C++ */

// Basic Libraries
int id_master = 1;
#include <iostream>
#include <sstream>
#include <fstream>
// Graphic Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ctime>
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
#include "vector2.h"
#include "Object.h"
#include "Properties.h"
#include "ball_prop.h"
#include "mt_prop.h"
#include "tether_prop.h"
#include "MT.h"
#include "ball.h"
#include "tether.h"

//#include "Integration.h"
#include "display.h"
#include "props_maker.h"
#include "ball_interactions.h"
#include "Interactions.h"
#include "Simulation.h"

Simulation sim;

// Import input file parser and ouput file writer...
#include "object_step.h"
#include "input.h"
#include "output.h"
#include "read_output.h"


int main(int argc, char* argv[])
{
    srand(time(0));
//  EulerIntegration(start, end, step_int, step_out, vals, pars);
    std::string filename = argv[1];
    float maxtime = std::stof(argv[2]);
    Parser pars;
    std::fstream fs(filename);
    pars.readfile(fs);
    Simulation sim2;
//    sim.run_write(maxtime);
//    system("python ./Kinesin_Gliding.py");
//    sim2.show();
    sim.run_play();
    return 0;
}















