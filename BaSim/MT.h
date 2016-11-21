
#include <cmath>

class MT: public Object{
public:
    
    float length, orientation; // This properties should be able to change in time, that is why they are not pointerss
    
    void shuffle()
    {
        x = xBound*srand()*0.8;
        y = yBound*srand()*0.8;
        orientation = 2*PI*srand();
    }
    
    float xp()
    {
        return x+length*cos(orientation);
    }
    
    float yp()
    {
        return y+length*sin(orientation);
    }
    
};

