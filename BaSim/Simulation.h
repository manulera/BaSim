#include <unordered_map>
class Simulation{

public:
    std::unordered_map<std::string, Props*> prop_dict;
    std::vector<Object*> all;
    std::vector<Ball*> balls;
    std::vector<MT*> mts;
    FILE * file;
    float t;
    float t_old;
    float t_max;
    float dt;
    unsigned int fcounter;
    //std::unordered_map<std::string, std::vector<int>> obj_dict;
    
    void add_prop(Props& prop)
    {
        using namespace std;
        pair<string, Props*> newkey (prop.name,&prop);
        prop_dict.insert(newkey);
    }
    Props* get_prop(std::string name)
    {
        return prop_dict[name];
    }
    void add_object(std::string keys[3], std::string prop_val)
    {
        Props* p = get_prop(keys[2]);
        std::cout << "\"new\" statement reached for " << keys[2] <<std::endl;
        if (p->type=="ball")
        {
            for (int i = 0; i < std::stoi(keys[1]); i++)
            {
                balls.push_back(static_cast<Ball*>(p->make(prop_val)));
                //This way there is a way to reference the object from the id, by all.at(id)
                all.push_back(balls.at(balls.size()-1));
            }
        }
        if (p->type=="MT")
        {
            for (int i = 0; i < std::stoi(keys[1]); i++)
            {
                mts.push_back(static_cast<MT*>(p->make(prop_val)));
                all.push_back(mts.at(mts.size()-1));
            }
        }
    }
    void step();
    void display_mts();
    void display_balls();
    void play_mts();
    void play_balls();
    void play();
    void display();
    int run_write();
    int run_play();
    void write();
    void inifile();
    int populate();
    int populate_props();
    int populate_objs();
    int show();
};

void Simulation::step()
{
    // Find pairs of possible interacting MTs and balls
    
    for (int i_b = 0; i_b < balls.size(); i_b++)
    {
        for (int i_m = 0; i_m < mts.size(); i_m++)
        {
            interaction(balls.at(i_b),mts.at(i_m),i_m,dt);
        }
        
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
}

int Simulation::run_play()
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
    while (!glfwWindowShouldClose(win)){
        t = glfwGetTime();
        dt = t - t_old;
        t_old = t;
        step();
        play();
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    fclose(file);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}

int Simulation::run_write()
{
    unsigned int counter = 0;
    t = 0.0;
    dt = 0.015625;
    t_max = 10;
    inifile();
    while (t < t_max)
    {
        if (counter++%10==0)
        {
            //std::cout << t << std::endl;
            write();
        }
    //t = dt*(float)counter;
        t += dt;
        step();
        
    }
    return 0;
}
