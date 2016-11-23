



class Ball: public Object{
public:
    float *speed, *bind_rate, *bind_range, *unbind_rate;
    int attached;
    
    
    void shuffle()
    {
        x = srand()*xBound;
        y = srand()*yBound;
    }
    
    Ball(): Object()
    {
    }
    
    void printinfo()
    {
        using namespace std;
        cout << "The object "<<  name << "is a " << "with properties:"<<endl;
        cout << "speed: " << speed << "bind_range" << &bind_range << endl;
    }
    void populate(std::string);
    void display()
    {
        glBegin(GL_POINTS);
        {
            if (attached)
            {
                glColor3f(1.0,0.0,0.0);
            }
            else
            {
                glColor3f(0.0,1.0,0.0);
            }
            glVertex2f(x/xBound, y/yBound);
        }
        glEnd();
    }
};












