#include <unordered_map>
#include <array>
class Props{
public:
    // This member variables will be present in all the different objects name
    
    std::string name;
    std::string type;
    
    float  x , y;

};

class Ballprops: public Props{
public:
    int number;
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
//    void make(Ball& myball) // Probably this could be set as a virtual function once all objects are also made hyerarchical
//    {
//        myball.speed = speed; // Instead of calling the whole list, use a pointer
//        myball.bind_range = bind_range; // The object properties are set by a pointer that points to a set of properties
//        myball.bind_rate = bind_rate;
//        myball.unbind_rate = unbind_rate;
//        myball.active = 1;
//        myball.shuffle();
//    }
};

Props* makeProps(std::string (&keys) [3], std::string prop_val)
{
    if (keys[1]=="ball") return new Ballprops(keys,prop_val);
    return 0;
}

//class Tubeprops{
//public:
//    float length;
//};



//
//class ObjectList{
//    
//public:
//    
//    enum {BALL,TUBE};
//    int count[2] = {0,0}; // This counts how much of each kind we introduced
//    std::vector<Ballprops> ballprops;
//    std::vector<Tubeprops> tubeprops;
//    std::unordered_map<std::string, std::array<int, 2>> dict;
//    
//    int BallPropMaker(std::string (&keys) [3], std::vector<std::string> pairs)
//    {
//        using namespace std;
//        string propname;
//        string value;
//        
//        Ballprops props;
//        props.name = keys[2];
//        
//        for (int i = 0;i <= pairs.size()-1;i+=2)
//        {
//            propname = pairs.at(i);
//            value = pairs.at(i+1);
//            std::cout << "round " << i << endl;
//            if (propname == "speed") props.speed=stof(value); continue;
//            if (propname == "binding_rate") props.bind_rate=stof(value); continue;
//            if (propname == "binding_range") props.bind_range=stof(value); continue;
//            if (propname == "unbinding_rate") props.unbind_rate=stof(value); continue;
//            std::cout << "propname is: "<< propname << std::endl;
//            return 1;
//        }
//        std::cout << "hello" <<std::endl;
//        ballprops.push_back(props);
//        return 0;
//    }
//    int BallMaker(int ind, int number)
//    {
//        for (int i = 0; i < number; i++)
//        {
//            ball[i].speed = ballprops.at(ind).speed; // Instead of calling the whole list, use a pointer
//            ball[i].bind_range = ballprops.at(ind).bind_range; // The object properties are set by a pointer that points to a set of properties
//            ball[i].bind_rate = ballprops.at(ind).bind_rate;
//            ball[i].unbind_rate = ballprops.at(ind).unbind_rate;
//            ball[i].active = 1;
//            ball[i].shuffle();
//        }
//        return 0;
//    }
//
//    
//    int set(std::string (&keys) [3], std::string prop_val)
//    {
//        int type;
//        std::cout << keys[1];
//        if (keys[1]=="ball") type=BALL;
//        else if (keys[1]=="fiber") type=TUBE;
//        else return 1;
//        
//        using namespace std;
//        
//        
//        pair<string, array<int, 2>> newkey (keys[2] , array<int, 2>{count[type],0});
//        count[type]++;
//        dict.insert(newkey);
//        vector<string> pairs = split(prop_val, ',');
//        
//        switch (type) {
//            case BALL: BallPropMaker(keys, pairs); break;
//            case TUBE: "nothing"; break;
//            default:
//                return 1;
//        }
//        
//        return 0;
//    }
//    
//    int make(std::string name, int number)
//    {
//        using namespace std;
//        array<int,2> coords = dict[name];
//        cout << endl<< "coords[1] is: "<< ballprops.at(0).name << endl;
//        switch (coords[0])
//        {
//                
//            case BALL: BallMaker(coords[1],number); break;
//            case TUBE: "nothing"; break;
//            default:
//                return 1;
//        }
//        
//        return 0;
//    }
//};
//
//ObjectList object_list;

