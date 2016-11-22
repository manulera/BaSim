

int Simulation::populate()
{
    populate_props();
    bool keep = false;
    do {
        
    }
    while (keep);
    return 0;
}





int Simulation::populate_props()
{
    using namespace std;
    file = fopen("Output_props.bs", "r");
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
            cout << "prop_str: "<< prop_str << endl;
            makeProps(prop_str);
            prop_str = "";
        }
    }
    return 0;
}

int Simulation::show()
{
    populate();
    std::cout << "reached" << std::endl;
    return 0;
}
