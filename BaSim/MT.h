
#include <cmath>

class MT: public Object{
public:
    
    float length, orientation; // This properties should be able to change in time, that is why they are not pointerss
    
    std::string str_spec()
    {
        
        return "";
    }
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
    void populate(std::string);
    void display()
    {
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        {
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(x/xBound, y/yBound);
            glVertex2f(xp()/xBound, yp()/yBound);
        }
        glEnd();
    }
};

