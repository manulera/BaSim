
#include <cmath>

class MT: public Object{
public:
    
    Vector2 orientation;
    float length; // This properties should be able to change in time, that is why they are not pointerss
    float* mobility;
    void set_orientation(float angle)
    {
        float a = cos(angle);
        orientation.XX = a;
        orientation.YY = sqrt(1-a*a);
    }
    std::string str_spec()
    {
        
        return "";
    }
    void shuffle()
    {
        position.shuffle(0.8);
        position.XX *= xBound;
        position.YY *= yBound;
        orientation.shuffle();
        orientation.normalize();
    }
    
    Vector2 plus_end()
    {
        return position + orientation*length;
    }
    
    void populate(std::string);
    void display();
};

