// Function to calculate the sum of the elements in a vector

int SumVect(std::vector<float> vect)
{
    float sum=0;
    for (int i = 0; i < vect.size(); i++)
    {
        sum+=vect.at(i);
    }
    return sum;
}


//This could still be improved, maybe a list of functions would solve this

struct Params{
    float S_B = ntubs*(mt_length*binding_range*2+PI*pow(binding_range,2)); //Surface where motors can bind
    float S_A = xBound*yBound*4-S_B; // The rest of the surface
    float L_I = ntubs*(2*mt_length+2*PI*binding_range); // The A-B interface length
};
Params pars;

float vals[3] = {static_cast<float>(nballs)*(pars.S_A/(pars.S_A+pars.S_B)),
                 static_cast<float>(nballs)-static_cast<float>(nballs)*(pars.S_A/(pars.S_A+pars.S_B)),
                 0.0};


float start = 0.0;
float end = 60.0;
float step_int = 0.0001;
int step_out =end/step_int/500;

// In order to have balls_B(t) we are going to store all of them in a circular list, with capacity for n elements, where n is the time that it takes the motors to go through the length of the MTs, divided by the integration step.

int circ_length=mt_length/(motor_speed*step_int);
std::vector<float>balls_bound_t(circ_length);
float suma=0.0;
void stepFun(float *v, Params p, float step, int ind)
{
    
    float balls_A = v[0];
    float balls_B = v[1];
    float balls_bound = v[2];
    
    float sumB = suma-balls_bound_t.at(ind);
    
    float dA = (p.L_I*diff*(balls_B/p.S_B-balls_A/p.S_A))*step;
    float dbound = (balls_B*binding_rate - balls_bound*unbinding_rate - sumB*binding_rate*motor_speed/mt_length*step)*step;
    float dB = -dA-dbound;
    suma+=balls_B-balls_bound_t.at(ind); //not certain about this -1
    balls_bound_t.at(ind)=balls_B;
    v[0]+=dA;
    v[1]+=dB;
    v[2]+=dbound;
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




std::vector <float> x_out = {};
std::vector <float> y_out = {};

// This function is far from perfect, but for now will do the job
void EulerIntegration(float start, float end,float step_int, int step_out, float *v, Params p)
{
    int count_steps = 0;
    for (float x=start; x<end; x+=step_int)
    {
        //std::cout << count_steps<<" / "<< circ_length <<std::endl;
        stepFun(v,p,step_int,count_steps%circ_length);
        count_steps++;
        if (count_steps%step_out==0)
        {
            //std::cout << count_steps*step_int<<" / " << v[2]<<std::endl;
            x_out.push_back(x);
            y_out.push_back(1-(v[0]+v[1])/nballs);
        }
        
    }

}

