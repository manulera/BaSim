
#include <cmath>

class MT: public Object{
public:
    
    MTprops * props;
    
    Vector2 orientation;
    float length; // This properties should be able to change in time, that is why they are not pointerss
    void set_orientation(float angle)
    {
        float a = cos(angle);
        orientation.XX = a;
        orientation.YY = sqrt(1-a*a);
    }
    std::string str_spec()
    {
        return "";
    }
    void shuffle()
    {
        position.shuffle(0.8);
        position.XX *= xBound;
        position.YY *= yBound;
        orientation.shuffle();
        orientation.normalize();
        length = 100;
    }
    
    Vector2 plus_end()
    {
        return position + orientation*length;
    }
    void write(FILE* file);
    void populate(std::string&,std::unordered_map<int, Object*>& ids_dict);
    void display();
    void readvals(const std::string& prop_val)
    {
        Object::readvals(prop_val);
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
                if (propname == "length") {length=stof(value); continue;}
                if (propname == "orientation") {set_orientation(stof(value)); continue;}
            }
        }
    }

    MT(Props * p,std::string prop_val): Object()
    {
        props = static_cast<MTprops *>(p);
        shuffle();
        readvals(prop_val);
    }
    MT(std::string& line,std::unordered_map<int, Object*>& ids_dict): Object()
    {
        populate(line, ids_dict);
    }
};

