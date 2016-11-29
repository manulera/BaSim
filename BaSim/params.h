
#include <cstdlib>
#include <vector>
#include <cmath>

const float PI = 3.14159265358979323846264338327950288;
float diff_master = 50;       // diffusion constant in pixel units
unsigned long seed = 1;   // seed for random number generator


//float release_rate = motor_speed*2/mt_length;

//Useful functions
//Calculate distance
float dist(float x1, float y1, float x2, float y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

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


void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    if (!s.empty())
    {
        split(s, delim, elems);
    }
    return elems;
}
