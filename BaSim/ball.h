
class Ball: public Object{
public:
    float *speed, *bind_rate, *bind_range, *unbind_rate, *stall_force;
    MT* attached = nullptr;
    
    std::string tetherlabel;
    Tether* tethered = nullptr;
    
    int attached_id = 0; // this is a bit redundant, but useful for output
    float tubref = -1.0; // goes from 0 to 1. Represents the position of a bound motor with respect to the minus end of the MT its bound to. -1 if the ball is not bound
    float stall = 1.0;
    void shuffle()
    {
        position.shuffle();
        position.XX *= xBound;
        position.YY *= yBound;
    }
    
    Ball(): Object()
    {
    }
    void tether(std::vector<Tether* >);
    void printinfo()
    {
        using namespace std;
        cout << "The object "<<  name << "is a " << "with properties:"<<endl;
        cout << "speed: " << speed << "bind_range" << &bind_range << endl;
    }
    void populate(std::string&,std::unordered_map<int, Object*>& ids_dict);
    void move_along(float dt);
    void bind(MT*,int where,float distval);
    int within(MT*, float * distval);
    void interact(std::vector<MT*> mts,float dt);
    void iterate_mts(std::vector<MT*> mts,float dt);
    void display();
    void pull_mt();
    void unbind();
    void write(FILE* file);
    std::string str_spec()
    {
        
        return "";
    }
};




