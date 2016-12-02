#include <unordered_map>
class Props;
class MTprops;
class Ballprops;
class Tetherprops;

class Object{
public:
    Vector2 position;
    Props* props; // does this have any use?
    int identifier;
    virtual void printinfo(){
        std::cout << "No type of object specified"<< std::endl;
    }

    Object()
    {
        //props = p;
        identifier = id_master++;
    }
    
    virtual void readvals(const std::string& prop_val)
    {
        // If the user gave values
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
                if (propname == "x") {position.XX=stof(value);continue;}
                if (propname == "y") {position.YY=stof(value); continue;}
                
                //if (propname == "attached") {newball->attached=stof(value); continue;} We will have to think about how to set to which mt we attach the objects
            }
        }

    }

    virtual void diffuse(float dt){};
    virtual void boundary();
    virtual void populate(std::string&, std::unordered_map<int, Object*> &ids_dict);
    virtual void display(){};
    virtual void write(FILE* file);
};
class MT;
class Ball;
class Tether;
