



class Ball: public Object{
public:
    bool active;
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
};












