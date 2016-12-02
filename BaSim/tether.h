
class Tether: public Object{
public:
    
    std::string label;
    float* force_k;
    void populate(std::string,std::unordered_map<int, Object*> &ids_dict);
    void display();
    void write(FILE* file);
};
