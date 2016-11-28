
class Ball: public Object{
public:
    float *speed, *bind_rate, *bind_range, *unbind_rate;
    MT* attached = nullptr;
    int attached_id = 0; // this is a bit redundant, but useful for output
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
    void move_along(float dt);
    void bind(MT*,int where,float distval);
    int within(MT*, float * distval);
    void interact(std::vector<MT*> mts,float dt);
    void iterate_mts(std::vector<MT*> mts,float dt);
    void display()
    {
        glBegin(GL_POINTS);
        {
            if (attached_id)
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
    void unbind()
    {
        if (rand01()>1.0-unbinding_rate*dt)
        {
            attached=0;
        }
    }
    void move(MT mti)
    {
        float dist0=speed*dt;
        x+=dist0*cos(mti.orientation);
        y+=dist0*sin(mti.orientation);
        if (dist(x,y,mti.posx,mti.posy)>mti.length||dist(x,y,mti.posxp(),mti.posyp())>mti.length)
            attached=false;
    }
};












