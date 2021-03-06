


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

void Simulation::write()
{
    fprintf(file, "\nframe_%u: time %f\n", fcounter++, t);
    fprintf(file, "\nballs:\n");
    for (int i=0; i < balls.size();i++)
    {
        Ball* b = balls.at(i);
        fprintf(file, "%u %f %f %u \n", b->identifier, b->x, b->y, b->attached_id);
    }
    fprintf(file, "\nmts:\n");
    for (int i=0; i < mts.size();i++)
    {
        MT* b = mts.at(i);
        fprintf(file, "%u %f %f %f %f\n", b->identifier, b->x, b->y, b->orientation, b->length);
    }
    fprintf(file, "\n");
}

