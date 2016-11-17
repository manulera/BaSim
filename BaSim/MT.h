
#include <cmath>

class MT: public Object{
public:
    
    float length, orientation; //From minus end
    
    void set()
    {
        x = xBound*srand()*0.8;
        y = yBound*srand()*0.8;
        length = mt_length;
        orientation = 2*PI*srand();
    }
//    
//    MT(): Object()
//    {
//        set();
//    }
    
    float xp()
    {
        return x+length*cos(orientation);
    }
    
    float yp()
    {
        return y+length*sin(orientation);
    }
    
};

