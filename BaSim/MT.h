
#include <cmath>

class MT: public Object{
public:
    
    Vector2 orientation;
    float length; // This properties should be able to change in time, that is why they are not pointerss
    
    void set_orientation(float angle)
    {
        orientation.XX = angle;
        orientation.YY = sqrt(1-angle*angle);
    }
    std::string str_spec()
    {
        
        return "";
    }
    void shuffle()
    {
        position.shuffle(0.8);
        orientation = Vector2(rand01(),1);
        orientation.norm();
    }
    
    Vector2 plus_end()
    {
        return position + orientation*length;
    }
    
    void populate(std::string);
    void display()
    {
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        {
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(position.XX/xBound, position.YY/yBound);
            glVertex2f(plus_end().YY/xBound, plus_end().YY/yBound);
        }
        glEnd();
    }
};

