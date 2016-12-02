class Ballprops: public Props{
public:
    // They must be specified
    float attached,speed, bind_rate, bind_range, unbind_rate, stall_force;
    
    std::string str_spec()
    {
        using namespace std;
        string result;
        
        result+="speed: " + to_string(speed) + "\n";
        result+="bind_rate: " + to_string(bind_rate) + "\n";
        result+="bind_range: " + to_string(bind_range) + "\n";
        result+="unbind_rate: " + to_string(unbind_rate) + "\n";
        
        return result;
    }
    
    Ballprops(std::string (&keys) [3], std::string prop_val): Props()
    {
        type = keys[1];
        name = keys[2];
        using namespace std;
        vector<string> pairs = split(prop_val, ',');
        string propname;
        string value;
        
        for (int i = 0;i <= pairs.size()-1;i+=2)
        {
            propname = pairs.at(i);
            value = pairs.at(i+1);
            if (propname == "speed") {speed=stof(value); continue;}
            if (propname == "bind_rate") {bind_rate=stof(value); continue;}
            if (propname == "bind_range") {bind_range=stof(value); continue;}
            if (propname == "unbind_rate") {unbind_rate=stof(value); continue;}
            if (propname == "diff") {diff=stof(value); continue;}
            if (propname == "stall_force") {stall_force=stof(value); continue;}
        }
    }
//    Object* make(std::string prop_val)
//    {
//        Ball* newball = new Ball;
//        ids.push_back(id_master);
//        
//        // Properties of the type
//        newball->type = &type;
//        newball->name = &name;
//        newball->diff = &diff;
//        
//        newball->speed = &speed;
//        newball->bind_rate = &bind_rate;
//        newball->bind_range = &bind_range;
//        newball->unbind_rate = &unbind_rate;
//        newball->stall_force = &stall_force;
//
//        // Properties of the object
//        
//        // Initialize with default values
//        newball->attached = 0;
//        newball->shuffle();
//        // If the user gave values
//        if (!prop_val.empty())
//        {
//            using namespace std;
//            string propname;
//            string value;
//            vector<string> pairs = split(prop_val, ',');
//            for (int i = 0;i <= pairs.size()-1;i+=2)
//            {
//                propname = pairs.at(i);
//                value = pairs.at(i+1);
//                if (propname == "x") {newball->position.XX=stof(value); continue;}
//                if (propname == "y") {newball->position.YY=stof(value); continue;}
//                if (propname == "tethered") {newball->tetherlabel=(value); continue;}
//                //if (propname == "attached") {newball->attached=stof(value); continue;} We will have to think about how to set to which mt we attach the objects
//            }
//        }
//        return newball;
//    }
    
};