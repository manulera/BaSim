
#include <cmath>

class MT{
public:
    
    float posx, posy, length, orientation; //From minus end
    
    void set()
    {
        posx = xBound*srand()*0.8;
        posy = yBound*srand()*0.8;
        length = mt_length;
        orientation = 2*PI*srand();
    }
    
    MT()
    {
        set();
    }
    
    float posxp()
    {
        return posx+length*cos(orientation);
    }
    
    float posyp()
    {
        return posy+length*sin(orientation);
    }
    
};

