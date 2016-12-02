
class Tether: public Object{
public:
    Tetherprops* props;
    std::string label;
    float* force_k;
    void populate(std::string,std::unordered_map<int, Object*> &ids_dict);
    void display();
    void write(FILE* file);
    void shuffle(){};
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
                if (propname == "label") {label=value; continue;}
            }
        }
    }
    Tether(Props * p,std::string prop_val): Object()
    {
        props = static_cast<Tetherprops *>(p);
        shuffle();
        readvals(prop_val);
    }
    Tether(std::string& line,std::unordered_map<int, Object*>& ids_dict): Object()
    {
        populate(line, ids_dict);
    }

};
