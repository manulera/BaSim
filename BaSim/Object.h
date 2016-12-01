#include <unordered_map>
class Object{
public:
    Vector2 position;
    int identifier;
    std::string *type;
    std::string *name;
    float *diff;
    virtual void printinfo(){
        std::cout << "No type of object specified"<< std::endl;
    }
    Object()
    {
        identifier = id_master++;
    }
    virtual void diffuse(float dt);
    virtual void boundary();
    virtual void populate(std::string&, std::unordered_map<int, Object*> &ids_dict);
    virtual void display(){};
    virtual void write(FILE* file){};
};
class MT;
class Ball;
class Tether;
