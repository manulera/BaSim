
#include <thread>
#include <chrono>
int Simulation::populate_props()
{
    using namespace std;
    fstream fs("Output_props.bs");
    string chunk="";
    string prop_str="";
    while(getline (fs, chunk))
    {
        if (!chunk.empty())
        {
            prop_str += chunk + "\n";
        }
        
        else
        {
            Props* p = makeProps(prop_str);
            std::pair<std::string, Props*> newkey (p->name,p);
            prop_dict.insert(newkey);
            prop_str = "";
        }
    }
    return 0;
}

int Simulation::populate_objs()
{
    using namespace std;
    fstream fs("Output_objs.bs");
    string line;
    string type;
    int idnum;
    char temp[10];
    bool ended=false;
    // store the objects in the vectors
    while(getline (fs, line) && !glfwWindowShouldClose(win))
    {
        if (line=="") continue;
        if (sscanf(line.c_str(), "%u", &idnum))
        {
            if (type=="balls")
            {
                balls.push_back(new Ball(line,*this));
            }
            else if (type=="mts")
            {
                mts.push_back(new MT(line, *this));
            }
            else if (type=="tethers")
            {
                tethers.push_back(new Tether(line, *this));
            }
        }
        else
        {
            sscanf(line.c_str(), "%s",temp);
            type = temp;
            type.pop_back();//remove the ":"
            if (type.substr(0,5)=="frame")
            {
                if (ended == 1) break;
                ended = 1;
            }
        }
    }
    for (int i =0; i < tethers.size(); i++)
    {
        all.push_back(tethers.at(i));
    }
    for (int i =0; i < mts.size(); i++)
    {
        all.push_back(mts.at(i));
    }
    for (int i =0; i < balls.size(); i++)
    {
        all.push_back(balls.at(i));
    }
    
//    cout << "length of ball: " << balls.size()<<endl;
//    cout << "length of mt: " << mts.size()<<endl;
//    cout << "length of tethers: " << tethers.size()<<endl;
//    cout << "length of all: " << all.size()<<endl;
    return 0;
}

void Object::populate(std::string &line, Simulation & s)
{
    char temp[10];
    sscanf(line.c_str(),"%u %s %f %f",
           &identifier, &temp, &position.XX, &position.YY);
    props = s.prop_dict[std::string(temp)];
    line = line.substr(line.find(',')+1);

    if (s.ids_dict.find(identifier)==s.ids_dict.end())
    {
        std::pair<int, Object*> newkey (identifier,this);
        s.ids_dict.insert(newkey);
    }
}

void Ball::populate(std::string &line, Simulation & s)
{
    Object::populate(line, s);
    props = static_cast<Ballprops *> (Object::props);
    int tube_id;
    int tether_id;
    
    sscanf(line.c_str(),"%u %u %f \n",
           &tether_id, &tube_id, &tubref);
    attached = static_cast <MT *> (s.ids_dict[tube_id]);
    tethered = static_cast <Tether *> (s.ids_dict[tether_id]);
}

void MT::populate(std::string &line, Simulation & s)
{
    Object::populate(line, s);
    props = static_cast<MTprops *> (Object::props);
    sscanf(line.c_str(),"%f %f %f",
           &orientation.XX,&orientation.YY,&length);
}

void Tether::populate(std::string line, Simulation & s)
{
    Object::populate(line, s);
    props = static_cast<Tetherprops *> (Object::props);
}

int Simulation::show()
{
    if (!glfwInit())
    {
        return -1;
    }
    graphs = glfwCreateWindow(xGraphs, yGraphs, "Graphs", NULL, NULL);
    win = glfwCreateWindow(xBound, yBound, "BaSim", NULL, NULL);
    if (!win){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    glfwGetFramebufferSize(win, &xBound, &yBound);

    using namespace std;
    populate_props();
    populate_objs();
    fstream fs("Output_objs.bs");
    string line;
    int idnum;
    while(getline (fs, line)&&!glfwWindowShouldClose(win))
    {
        if (line=="") continue;
        if (sscanf(line.c_str(), "%u", &idnum))
        {
            // If at some points objects are destroyed, then  
            ids_dict[idnum]->populate(line, *this);
        }
        else if ((line.find("frame")!=std::string::npos))
        {
            play();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    fclose(file);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
