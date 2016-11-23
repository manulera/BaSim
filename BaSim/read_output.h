
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

void Ball::populate(std::string line)
{
    int dummy;
    std::scanf(line.c_str(),"%u %f %f %u",dummy,x,y,attached);
}

void MT::populate(std::string line)
{
    int dummy;
    std::scanf(line.c_str(),"%u %f %f %f",dummy,x,y,length);
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
    fstream fs("Output_objs.bs");
    string line;
    unsigned int counter=0;
    int idnum = -1;
    while(getline (fs, line)&&!glfwWindowShouldClose(win))
    {
        std::cout << line.c_str() <<std::endl;
        //scanf(line.c_str(), "%u",idnum); reached(idnum);
        {
//            reached();
//            Object* obj= all.at(idnum);
//            if (*obj->type=="ball") obj=static_cast<Ball*>(obj);
//            if (*obj->type=="MT") obj=static_cast<MT*>(obj);
//            all.at(idnum)->populate(line);
        }
        
      //  else if (scanf(line.c_str(), "frame_",temp) && counter%10==1)
        {
//            reached();
//            play();
//            glfwSwapBuffers(win);
//            glfwPollEvents();
        }
        reached(counter);
        counter++;
        idnum = -1;
    }
    
    fclose(file);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
