
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
            makeProps(prop_str);
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
    int idmax = 0;
    char temp[10];
    bool ended=false;
    int num = 0;
    // store the objects in the vectors
    while(getline (fs, line)&&!glfwWindowShouldClose(win))
    {
        num++;
        if (line=="") continue;
        if (sscanf(line.c_str(), "%u", &idnum))
        {
            if (idmax<idnum) {idmax=idnum;}
            if (type=="balls")
            {
                balls.push_back(new Ball);
                balls.at(balls.size()-1)->populate(line);
            }
            if (type=="mts")
            {
                mts.push_back(new MT);
                mts.at(mts.size()-1)->populate(line);
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
    all.resize(idmax);
    for (int i =0; i < balls.size(); i++)
    {
        all.at(balls.at(i)->identifier-1)=balls.at(i);
    }
    for (int i =0; i < mts.size(); i++)
    {
        all.at(mts.at(i)->identifier-1)=mts.at(i);
    }
//    cout << "length of ball: " << balls.size()<<endl;
//    cout << "length of mt: " << mts.size()<<endl;
//    cout << "length of all: " << all.size()<<endl;
    return 0;
}

void Ball::populate(std::string line)
{
    sscanf(line.c_str(),"%u %f %f %u",&identifier,&x,&y,&attached_id);
}

void MT::populate(std::string line)
{
    sscanf(line.c_str(),"%u %f %f %f %f",&identifier,&x,&y,&orientation,&length);
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
            all.at(idnum-1)->populate(line);
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
