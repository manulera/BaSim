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
};

class Props{
public:
    
    // This member variables will be present in all the different objects name
    std::string name;
    std::string type;
    
    float  x , y;
    virtual Object* make(){return 0;};
};
