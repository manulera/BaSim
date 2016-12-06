
#include <cmath>

class MT: public Object{
public:
    
    MTprops * props;
    
    // This properties should be able to change in time, that is why they are not pointers
    
    Vector2 orientation;
    float length;
    float inertia()
    {
        // I guess mass/density will be included at some point, but so far everything has the same density of mass, being one.
        return 0.000001*length*length*length/12;
    }
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
    
    void ref_minus() // In case the coordinates we give in the config file are from the minus end
    {
        position += orientation * length/2;
    }
    
    Vector2 plus_end()
    {
        return position + orientation*length/2;
    }
    Vector2 minus_end()
    {
        return position - orientation*length/2;
    }
    void write(FILE* file);
    void populate(std::string&,Simulation &);
    void display();
    void readvals(const std::string& prop_val)
    {
        int do_ref_minus = 0;
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
                if (propname == "ref_minus") {do_ref_minus = stoi(value); continue;}
            }
            if (do_ref_minus)
            {
                ref_minus();
            }
        }
    }

    MT(Props * p,std::string prop_val): Object()
    {
        Object::props = p;
        props = static_cast<MTprops *>(p);
        shuffle();
        readvals(prop_val);
    }
    MT(std::string& line,Simulation & s): Object()
    {
        populate(line, s);
    }
};

