
//This could still be improved, maybe a list of functions would solve this

struct Params{
    float S_B = ntubs*(mt_length*binding_range*2+PI*pow(binding_range,2)); //Surface where motors can bind
    float S_A = xBound*yBound*2-S_B; // The rest of the surface
    float L_I = ntubs*(2*mt_length+2*PI*binding_range); // The A-B interface length
};
Params pars;

float vals[2] = {static_cast<float>(nballs)*(pars.S_A/(pars.S_A+pars.S_B)),
                     static_cast<float>(nballs)-static_cast<float>(nballs)*(pars.S_A/(pars.S_A+pars.S_B))};



void stepFun(float *v, Params p, float step)
{
    float balls_A = v[0];
    float balls_B = v[1];
    float dA = p.L_I*diff*(balls_B/p.S_B-balls_A/p.S_A);
    float dB = -dA;
    //-balls_B*binding_rate*step;
    
    v[0]+=dA*step;
    v[1]+=dB*step;
    //std::cout << balls_B/p.S_B << ";" << balls_A/p.S_A<< "/"<< balls_B/p.S_B-balls_A/p.S_A<< std::endl;
    //std::cout << balls_B+balls_A << std::endl;
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


float start = 0.0;
float end = 60.0;
float step_int = 0.0001;
int step_out = 5000;

std::vector <float> x_out = {};
std::vector <float> y_out = {};

// This function is far from perfect, but for now will do the job
void EulerIntegration(float start, float end,float step_int, int step_out, float *v, Params p)
{
    //std::cout << v[0] << "," <<v[1] << std::endl;
    int count_steps = 0;
    
    for (float x=start; x<end; x+=step_int)
    {
        stepFun(v,p,step_int);
        count_steps++;
        if (count_steps==step_out)
        {
            count_steps=0;
            x_out.push_back(x);
            //std::cout << v[0] << "," <<v[1] << std::endl;
            y_out.push_back((v[0]+v[1])/nballs);
        }
    }

    for (int i=0;i<y_out.size();i++)
    {
        //std::cout<<y_out.at(i) << std::endl;
    }
}



//float a = EulerIntegration(0.0,60.0,0.01,&vals,pars, &dB_dt);