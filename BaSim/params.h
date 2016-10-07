


#include <cstdlib>
#include <vector>
#include <cmath>

const float PI = 3.14159265358979323846264338327950288;
float diff     = 5000;       // diffusion constant in pixel units
unsigned long seed = 1;   // seed for random number generator
float alpha    = 0;       //diffusive motion within interval dt

float motor_speed = 0.0;
float binding_rate = 0.5;
float binding_range = 5;
float mt_length = 100;

const int nballs = 500;
const int ntubs = 100;

//Useful functions
/// signed random real in [-1, 1]
float srand()
{
    const float scale = 2.0 / static_cast<float>(RAND_MAX);
    return static_cast<float>( random() ) * scale - 1.0;
}

/// positive random real in ]0, 1]
float prand()
{
    const float scale = 1.0 / ( 1+static_cast<float>(RAND_MAX) );
    return static_cast<float>( 1+random() ) * scale;
}
/// positive random real in [0, 1]
float rand01()
{
    return random()/static_cast<float>(RAND_MAX);
}

// Graphics

int xBound=640;
int yBound=480;
int xGraphs=800;
int yGraphs=200;

GLFWwindow *win;
GLFWwindow *graphs;

std::vector <float> time_vect = {0.0};
std::vector <float> bound_vect = {0.0};
std::vector <float> region_vect = {0.0}; //sloppy

float time_lim = 60.0; // In seconds
float y_lim = 1.0;
float graph_xBound = 0.1;
float graph_yBound = 0.1;

