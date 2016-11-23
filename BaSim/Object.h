class Object{
public:
    float x, y;
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
    virtual void diffuse();
    virtual void boundary();
    virtual void populate(std::string){};
    virtual void display(){};
};

