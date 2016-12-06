
class Ball: public Object{
public:

    MT* attached = nullptr;
    std::string tetherlabel;
    Tether* tethered = nullptr;
    Ballprops* props;
    float tubref = -1.0; // goes from 0 to 1. Represents the position of a bound motor with respect to the minus end of the MT its bound to. -1 if the ball is not bound
    float stall = 1.0;
    void shuffle()
    {
        position.shuffle();
        position.XX *= xBound;
        position.YY *= yBound;
        attached = 0;
    }
    void readvals(const std::string& prop_val)
    {
        Object::readvals(prop_val);
        if (!prop_val.empty())
        {
            using namespace std;
            string propname;
            string value;
            vector<string> pairs = split(prop_val, ',');
            for (int i = 0;i <= pairs.size()-1;i+=2)
            {
                propname = pairs.at(i);
                value = pairs.at(i+1);
                if (propname == "tethered") {tetherlabel=(value); continue;}
                //if (propname == "attached") {newball->attached=stof(value); continue;} We will have to think about how to set to which mt we attach the objects
            }
        }
    }
    
    Ball(Props * p,const std::string& prop_val): Object()
    {
        Object::props = p;
        props = static_cast<Ballprops *>(p);
        shuffle();
        readvals(prop_val);
    }
    
    Ball(std::string& line, Simulation & s): Object()
    {
        populate(line, s);
    }
    
    void tether(std::vector<Tether* >);
    void printinfo()
    {
        using namespace std;
        cout << "The object "<<  props->name << "is a " << "with properties:"<<endl;
        cout << "speed: " << props->speed << "bind_range" << props->bind_range << endl;
    }
    void move_along(float dt);
    void populate(std::string&,Simulation&);
    void bind(MT*,int where,float distval);
    int within(MT*, float * distval);
    void interact(std::vector<MT*> mts,float dt);
    void iterate_mts(std::vector<MT*> mts,float dt);
    void display();
    void pull_mt(float dt);
    void unbind();
    void write(FILE* file);
    void diffuse(float dt);
    std::string str_spec()
    {
        
        return "";
    }
};




