class Ballprops: public Props{
public:
    // They must be specified
    float attached,speed, bind_rate, bind_range, unbind_rate;
    
    Ballprops(std::string (&keys) [3], std::string prop_val): Props()
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
            std::cout << "propname written: "<< propname << std::endl;
            value = pairs.at(i+1);
            if (propname == "speed") speed=stof(value); continue;
            if (propname == "binding_rate") bind_rate=stof(value); continue;
            if (propname == "binding_range") bind_range=stof(value); continue;
            if (propname == "unbinding_rate") unbind_rate=stof(value); continue;
            
        }
    }
    
    Object* make()
    {
        Ball* newball = new Ball;
        newball->name = &name;
        newball->speed = &speed;
        newball->bind_rate = &bind_rate;
        newball->bind_range = &bind_range;
        newball->unbind_rate = &unbind_rate;
        newball->attached = 0;
        newball->shuffle();
        return newball;
    }

};