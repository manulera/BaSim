
//This could still be improved, maybe a list of functions would solve this

struct Params{
    float S_B = ntubs*(mt_length*binding_range*2+PI*pow(binding_range,2)); //Surface where motors can bind
    float S_A = xBound*yBound*2-S_B; // The rest of the surface
    float L_I = ntubs*(2*mt_length+2*PI*binding_range); // The A-B interface length
};
Params pars;

struct Values{
    float balls_A = nballs*(pars.S_A/(pars.S_A+pars.S_B));
    float balls_B = nballs-balls_A;
};
Values vals;

float ini_vals[2] = {nballs*(pars.S_A/(pars.S_A+pars.S_B)),
                     nballs-nballs*(pars.S_A/(pars.S_A+pars.S_B))};



void stepFun(float *v, Params p, float step)
{
    float balls_A = v[0];
    float balls_B = v[1];
    float dA = p.L_I*diff*(balls_B/p.S_B-balls_A/p.S_A);
    float dB = -dA-balls_B*binding_rate;
    
    v[0]+=dA*step;
    v[1]+=dB*step;
}

// Euler method
// Create a vector of evenly spaced numbers.
std::vector<float> range(float min, float max, size_t N)
{
    std::vector<float> range;
    float delta = (max-min)/float(N-1);
    for(int i=0; i<N; i++)
    {
        range.push_back(min + i*delta);
    }
    return range;
}

std::vector <float> x_vect = range(0.0,60.0,0.01);
std::vector <float> y_vect = {};
void EulerIntegration (float v, Params p, Values (*myStepFun)(float*,Params,float), std::vector<float> &x, std::vector<float> *y) //why???
{
    for (int i=0;i<x.size();i++)
    {
        myStepFun(&v,p,step);
    }

}


float a = EulerIntegration(0.0,60.0,0.01,&vals,pars, &dB_dt);