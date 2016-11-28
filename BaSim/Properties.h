class Props{
public:
    
    // This member variables will be present in all the different objects name
    std::string name;
    std::string type;
    std::vector<int> ids;
    float  x , y;
    virtual Object* make(std::string prop_val){return 0;};
    virtual std::string str_spec(){return "";};
    std::string str()
    {
        std::string result;
        result+="name: " + name + "\n";
        result+="type: " + type + "\n";
        result+=str_spec();
//        for (int i = 0; i<ids.size(); i++)
//        {
//            result+= std::to_string(ids.at(i)) + ", ";
//        }
//        result.pop_back(); result.pop_back();
        return result;
    }
};
