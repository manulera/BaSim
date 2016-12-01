


void Simulation::inifile()
{
    fcounter = 0;
    file = fopen("Output_props.bs", "w");
    for (auto i = prop_dict.begin(); i!=prop_dict.end() ;i++)
    {
        Props* p = i->second;
        fprintf(file, "%s\n",p->str().c_str());
    }
    fclose(file);
    file = fopen("Output_objs.bs", "w");
    fprintf(file, "");
    fclose(file);
    file = fopen("Output_objs.bs", "a");
}

void Tether::write(FILE * file)
{
    fprintf(file, "%u %f %f, \n",
            identifier, position.XX, position.YY);
}

void MT::write(FILE * file)
{
    fprintf(file, "%u %f %f, %f %f %f\n",
            identifier, position.XX, position.YY, orientation.XX, orientation.YY, length);
}


void Ball::write(FILE * file)
{
    int tube_id = 0;
    int tether_id = 0;
    if (attached) {tube_id = attached->identifier;}
    if (tethered) {tether_id = tethered->identifier;}
    fprintf(file, "%u %f %f, %u %u %f \n",
            identifier, position.XX, position.YY, tether_id, tube_id, tubref);

}
void Simulation::write()
{
    fprintf(file, "\nframe_%u: time %f\n", fcounter++, t);
    
    fprintf(file, "\ntethers:\n");
    for (int i=0; i < tethers.size();i++)
    {
        tethers.at(i)->write(file);
    }
    
    fprintf(file, "\nmts:\n");
    for (int i=0; i < mts.size();i++)
    {
        mts.at(i)->write(file);
    }

    fprintf(file, "\nballs:\n");
    for (int i=0; i < balls.size();i++)
    {
        balls.at(i)->write(file);
    }
    
    fprintf(file, "\n");
}

