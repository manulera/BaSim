class MTprops: public Props{
public:
    // They must be specified
    float length,orientation;
    
    MTprops(std::string (&keys) [3], std::string prop_val): Props()
    {
        type = keys[1];
        name = keys[2];

        if (!prop_val.empty())
        {
            using namespace std;
            string propname;
            string value;
            vector<string> pairs = split(prop_val, ',');
            for (int i = 0;i < pairs.size();i+=2)
            {
                propname = pairs.at(i);
                value = pairs.at(i+1);
                // No props yet
            }
        }
    }
    
    Object* make(std::string prop_val)
    {
        MT* newmt = new MT;
        ids.push_back(id_master);
        
        // Properties of the object
        newmt->type = &type;
        newmt->name = &name;
        
        // Initialize default values
        newmt->length = 100;
        newmt->shuffle();
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
                if (propname == "x") {newmt->position.XX=stof(value); continue;}
                if (propname == "y") {newmt->position.YY=stof(value); continue;}
                if (propname == "attached") {newmt->length=stof(value); continue;}
                if (propname == "orientation") {newmt->set_orientation(stof(value)); continue;}
            }
        }
        return newmt;
    }
    
};