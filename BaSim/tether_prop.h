class Tetherprops: public Props{
public:
    // They must be specified
    float force_k;
    Tetherprops(std::string (&keys) [3], std::string prop_val): Props()
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
                if (propname == "diff") {diff=stof(value); continue;}
                if (propname == "force_k") {force_k=stof(value); continue;}
            }
        }
    }
    
//    Object* make(std::string prop_val)
//    {
//        Tether* newt = new Tether;
//        ids.push_back(id_master);
//        
//        // Properties of the object
//        newt->type = &type;
//        newt->name = &name;
//        newt->diff = &diff;
//        newt->force_k = &force_k;
//        
//        // Initialize default values
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
//                if (propname == "x") {newt->position.XX=stof(value); continue;}
//                if (propname == "y") {newt->position.YY=stof(value); continue;}
//                if (propname == "label") {newt->label=value; continue;}
//            }
//        }
//        return newt;
//    }
    
};