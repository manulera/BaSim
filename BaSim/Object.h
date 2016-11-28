class Object{
public:
    Vector2 position;
    int identifier;
    std::string *type;
    std::string *name;
    virtual void printinfo(){
        std::cout << "No type of object specified"<< std::endl;
    }
    Object()
    {
        identifier = id_master++;
    }
    virtual void diffuse(float dt);
    virtual void boundary();
    virtual void populate(std::string){};
    virtual void display(){};
};
class MT;
class Ball;

