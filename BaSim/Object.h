class Object{
public:
    float x, y;
    std::string *type;
    std::string *name;
    virtual void make(Props& prop){}
    virtual void printinfo(){
        std::cout << "No type of object specified"<< std::endl;
    }
    Object(Props& prop)
    {
        make(prop);
    }
};

