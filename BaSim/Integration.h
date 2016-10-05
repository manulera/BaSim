

struct Params{
    float S_B = ntubs*(mt_length*binding_range*2+PI*pow(binding_range,2)); //Surface where motors can bind
    float S_A = xBound*yBound*2-S_A; // The rest of the surface
    float L_I = ntubs*(2*mt_length+2*PI*binding_range); // The A-B interface length
};

Params pars;
struct Values{
    float balls_A = nballs*(pars.S_A/(pars.S_A+pars.S_B));
    float balls_B = nballs-balls_A;
};
Values vals;

float dA_dt(Values v, Params p)
{
    return p.L_I*diff*(v.balls_B/p.S_B-v.balls_A/p.S_A);
}
float dB_dt(Values v, Params p)
{
    return -dA_dt(v,p)-v.balls_B*binding_rate;
}



// Euler method
float EulerIntegration(float start, float end, float step, Values v, Params p, float (*fun)(Values,Params))
{
    float sum=0.0;
    for (float x=start; x<end; x+=step)
    {
        
    }
    return 2;
}


float a = EulerIntegration(0.0,60.0,0.01,vals,pars, &dB_dt);