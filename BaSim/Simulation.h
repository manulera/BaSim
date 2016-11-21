#include <unordered_map>
class Simulation{

public:
    std::unordered_map<std::string, Props*> prop_dict;
    std::vector<Ball*> balls;
    std::vector<MT*> mts;
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
    void add_object(std::string name)
    {
        using namespace std;
        Props* p = get_prop(name);
        if (p->type=="ball")
        {
            balls.push_back(static_cast<Ball*>(p->make()));
        }
        if (p->type=="MT")
        {
            mts.push_back(static_cast<MT*>(p->make()));
        }
            
    }
    void step();
    void display_mts();
    void display_balls();
    void display();
    int run();
};

void Simulation::step()
{
    // Find pairs of possible interacting MTs and balls
    
    for (int i_b = 0; i_b < balls.size(); i_b++)
    {
        for (int i_m = 0; i_m < mts.size(); i_m++)
        {
            interaction(balls.at(i_b),mts.at(i_m),i_m);
        }
        
    }
}

void Simulation::display_mts()
{
    for (int j=0; j<mts.size(); j++)
    {
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        {
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(mts.at(j)->x/xBound, mts.at(j)->y/yBound);
            glVertex2f(mts.at(j)->xp()/xBound, mts.at(j)->yp()/yBound);
        }
        glEnd();
    }

}

void Simulation::display_balls()
{
    for (int i=0; i<balls.size(); i++)
    {
        glBegin(GL_POINTS);
        {
            if (!balls.at(i)->attached)
            {
                glColor3f(1.0,0.0,0.0);
            }
            else
            {
                glColor3f(0.0,1.0,0.0);
            }
            glVertex2f(balls.at(i)->x/xBound, balls.at(i)->y/yBound);
        }
        glEnd();
        //        glBegin(GL_POINTS);
        //        {
        //            glColor3f(1.0,1.0,0.0);
        //            glVertex2f(xBound,yBound);
        //        }
        //        glEnd();
        
    }
}

void Simulation::display()
{
    glClearColor(0.0f, 0.0f,0.0f,1.0f);
    glfwMakeContextCurrent(graphs);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwMakeContextCurrent(win);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    
    //MT
    display_mts();
    
    //Motors
    display_balls();
    
    // Update the graphs
    //    time_vect.push_back(time_vect.at(time_vect.size()-1)+dt);
    //    bound_vect.push_back(static_cast<float>(CountBound())/static_cast<float>(nballs));
    //    region_vect.push_back(static_cast<float>(CountArea())/static_cast<float>(nballs));
    //    graphsRefresh();
}

int Simulation::run()
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
    if (!glewInit()) return -1;
    
    //glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glfwMakeContextCurrent(win);
    glfwGetFramebufferSize(win, &xBound, &yBound);

    while (!glfwWindowShouldClose(win)){
        t = glfwGetTime();
        dt = t - t_old;
        t_old = t;
        step();
        display();
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
