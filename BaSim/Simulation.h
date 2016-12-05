#include <unordered_map>
class Simulation{

public:
    std::unordered_map<std::string, Props*> prop_dict;
    std::unordered_map<int, Object*> ids_dict;
    std::vector<Object*> all;
    std::vector<Ball*> balls;
    std::vector<MT*> mts;
    std::vector<Tether*> tethers;
    FILE * file;
    float t;
    float t_old;
    float t_max;
    float dt;
    unsigned int fcounter;
    Simulation()
    {
        std::pair<int, Object*> newkey (0,nullptr);
        ids_dict.insert(newkey); // referencing to zero returns a nullptr
    }
    Props* get_prop(std::string name)
    {
        return prop_dict[name];
    }
    void add_object(std::string keys[3], std::string prop_val);
    void add_prop(Props&);
    void step();
    void display_mts();
    void display_balls();
    void play_mts();
    void play_balls();
    void play();
    void display();
    int run_write(float);
    int run_play();
    void write();
    void inifile();
    int populate();
    int populate_props();
    int populate_objs();
    int show();
    void inisim();
};

void Simulation::add_object(std::string keys[3], std::string prop_val)
{
    Props* p = get_prop(keys[2]);
    if (p->type=="ball")
    {
        for (int i = 0; i < std::stoi(keys[1]); i++)
        {
            Ball* obj =new Ball(p, prop_val);
            balls.push_back(obj);
            all.push_back(obj);
            std::pair<int, Object*> newkey (obj->identifier,obj);
        }
    }
    if (p->type=="MT")
    {
        for (int i = 0; i < std::stoi(keys[1]); i++)
        {
            MT* obj =new MT(p, prop_val);
            mts.push_back(obj);
            all.push_back(obj);
            std::pair<int, Object*> newkey (obj->identifier,obj);
        }
    }
    if (p->type=="tether")
    {
        for (int i = 0; i < std::stoi(keys[1]); i++)
        {
            Tether* obj =new Tether(p, prop_val);
            tethers.push_back(obj);
            all.push_back(obj);
            std::pair<int, Object*> newkey (obj->identifier,obj);
        }
    }

}

void Simulation::add_prop(Props& prop)
{
    using namespace std;
    pair<string, Props*> newkey (prop.name,&prop);
    prop_dict.insert(newkey);
}


void Simulation::step()
{
    for (int i = 0; i < balls.size(); i++)
    {
        balls.at(i)->interact(mts,dt);
    }
}

void Simulation::play()
{
    glClearColor(0.0f, 0.0f,0.0f,1.0f);
    glfwMakeContextCurrent(graphs);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwMakeContextCurrent(win);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    
    for (int j=0; j<all.size(); j++)
    {
        all.at(j)->display();
    }
    
    // Update the graphs
    //    time_vect.push_back(time_vect.at(time_vect.size()-1)+dt);
    //    bound_vect.push_back(static_cast<float>(CountBound())/static_cast<float>(nballs));
    //    region_vect.push_back(static_cast<float>(CountArea())/static_cast<float>(nballs));
    //    graphsRefresh();
    
    glfwSwapBuffers(win);
    glfwPollEvents();
}

int Simulation::run_play()
{
    inisim();
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
    while (!glfwWindowShouldClose(win)){
        t = glfwGetTime();
        dt = 0.001;
        t_old = t;
        step();
        play();
    }
    fclose(file);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}

void Simulation::inisim()
{
    for (int i = 0; i < balls.size(); i++)
        if (!balls.at(i)->tetherlabel.empty())
        {
            balls.at(i)->tether(tethers);
        }
}

int Simulation::run_write(float maxt)
{
    unsigned int counter = 0;
    t = 0.0;
    dt = 0.015625;
    t_max = maxt;
    float percent = t_max/10;
    int percent_i = 1;
    inisim();
    inifile();
    while (t < t_max)
    {
        if (counter++%10==0)
        {
            write();
        }
        if (t>percent*percent_i)
        {
            std::cout << percent_i<< "0% completed " << std::endl;
            percent_i++;
        }
    //t = dt*(float)counter;
        t += dt;
        step();
        
    }
    fclose(file);
    std::cout << "Succesfully finished" << std::endl;
    return 0;
}
