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

// Graphic Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <cstdlib>
#include <cmath>
float t = 0.0; float t_old=0.0; float dt=0.0;

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

// Import input file parser and ouput file writer...
#include "props_maker.h"
#include "Interactions.h"
#include "Simulation.h"
Simulation sim;

#include "object_step.h"
#include "ball_step.h"
#include "input.h"
#include "output.h"


//MT mt[250];

// Initialize internal variables for the simulation
//
//int CountBound()
//{
//    int counter=0;
//    for(int i = 0; i < nballs; i++)
//    {
//        counter+=!!ball[i].attached;
//    }
//    return counter;
//}
//int CountArea()
//{
//    int counter=0;
//    for(int i = 0; i < nballs; i++)
//    {
//        counter+=ball[i].x<0;
//    }
//    return counter;
//}
//
//void display()
//{
//    glClearColor(0.0f, 0.0f,0.0f,1.0f);
//    glfwMakeContextCurrent(graphs);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glfwMakeContextCurrent(win);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glPointSize(5);
//    
//    //MT
//    for (int j=0; j<ntubs; j++)
//    {
//
//    glLineWidth(2.0f);
//    glBegin(GL_LINES);
//    {
//        glColor3f(0.0, 0.0, 1.0);
//        glVertex2f(mt[j].x/xBound, mt[j].y/yBound);
//        glVertex2f(mt[j].xp()/xBound, mt[j].yp()/yBound);
//    }
//    glEnd();
//    }
//    
//    
//    //Motors
//    for (int i=0; i<nballs; i++)
//    {
//
//        for (int j=0; j<ntubs; j++)
//        {
//            ball[i].step(mt[j],j);
//        }
//        glBegin(GL_POINTS);
//        {
//            if (!ball[i].attached)
//                {glColor3f(1.0,0.0,0.0);}
//            else
//                {
//                glColor3f(0.0,1.0,0.0);}
//            glVertex2f(ball[i].x/xBound, ball[i].y/yBound);
//        }
//        glEnd();
//        glBegin(GL_POINTS);
//        {
//            glColor3f(1.0,1.0,0.0);
//            glVertex2f(xBound,yBound);
//        }
//        glEnd();
//        
//    }
//    
//
//    // Update the graphs
//    time_vect.push_back(time_vect.at(time_vect.size()-1)+dt);
//    bound_vect.push_back(static_cast<float>(CountBound())/static_cast<float>(nballs));
//    region_vect.push_back(static_cast<float>(CountArea())/static_cast<float>(nballs));
//    graphsRefresh();
//}

int main() {
//    EulerIntegration(start, end, step_int, step_out, vals, pars);

    Parameters param;
    param.parseFile("config.bs");
    std::cout << sim.mts.size() << std::endl;
    //std::cout << sim.objects.at(0)->x << std::endl;
    return sim.run();
}















