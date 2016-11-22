class MTprops: public Props{
public:
    // They must be specified
    float length,orientation;
    
    MTprops(std::string (&keys) [3], std::string prop_val): Props()
    {
        using namespace std;
        vector<string> pairs = split(prop_val, ',');
        type = keys[1];
        name = keys[2];
        string propname;
        string value;
        for (int i = 0;i <= pairs.size()-1;i+=2)
        {
            propname = pairs.at(i);
            value = pairs.at(i+1);
            if (propname == "length") length=stof(value); continue;
            if (propname == "orientation") orientation=stof(value); continue;
        }
    }
    
    Object* make()
    {
        MT* newmt = new MT;
        ids.push_back(id_master);
        newmt->type = &type;
        newmt->name = &name;
        newmt->length = length;
        newmt->shuffle();
        return newmt;
    }
    
};