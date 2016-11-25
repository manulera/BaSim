
int Ball::within(MT* mti , float* distval)

//    /* Function that determines if a motor is close to a MT by a distance of 'range'.
//        + Returns 0 if its further than range
//        + Returns 1 if its in range from the minus end
//        + Returns 2 if its in range from the plus end
//        + Returns 3 if its in range from the body of the MT
//     */
{
    // This is based on the notes of the notebook
    
    float a = dist(x,y,mti->x,mti->y); //Distance from the minus end
    float b = dist(x,y,mti->xp(),mti->yp()); //Distance from the plus end
    float c = mti->length;
    float h = sqrt(a*a-pow((a*a-b*b+c*c)/2/c,2));
    if ((b*b+c*c<a*a) && (a>=b)) // Plus end
    {*distval = dist(x,y,mti->xp(),mti->yp());
        return (*distval < *(bind_range))*2;}
    else if ((a*a+c*c<b*b) && (a<=b)) // Minus end
    {*distval = dist(x,y,mti->x+mti->x,mti->y);
        return (*distval < *(bind_range))*1;}
    else //Body of the microtubule
    {*distval = h;
        return (*distval < *(bind_range))*3;}
}

void Ball::move_along(float dt)
{
    // dist0 is the distance that the motors travels in dt
    float dist0 = *speed * dt;
    x+=dist0*cos(attached->orientation);
    y+=dist0*sin(attached->orientation);
    if (dist(x,y,attached->x,attached->y)>attached->length||dist(x,y,attached->xp(),attached->yp())>attached->length)
    {
        attached=nullptr;
        attached_id=0;
    }
}

void Ball::bind(MT * mti, int where, float distval)
{
    attached = mti;
    attached_id = mti->identifier;
    //glLineWidth(1);
    //glBegin(GL_LINES);
    {
        //glVertex2f(x/xBound, y/yBound);
        if (where==1) //Bind to minus end
        {
            x=mti->x;
            y=mti->y;
        }
        else if (where==2) //Bind to plus end
        {
            x=mti->xp();
            y=mti->yp();
            
        }
        else if (where==3) //Bind to body
        {
            float a = dist(x,y,mti->x,mti->y); //Distance from the minus end
            float dist0 = sqrt(std::abs(a*a-distval*distval)); // There are cases where this is negative
            x=mti->x+dist0*cos(mti->orientation);
            y=mti->y+dist0*sin(mti->orientation);
        }
        //glVertex2f(x/xBound, y/yBound);
    }
    //glEnd();
}

void Ball::iterate_mts(std::vector<MT*> mts,float dt)
{
    float distval;
    for (int i = 0; i<mts.size(); i++)
    {
        if (rand01()<*bind_rate*8*dt)
        {
            int wherebind = within(mts.at(i),&distval);
            if (wherebind&&rand01()<0.125)
            {
                bind(mts.at(i),wherebind, distval);
            }
        }
        else
        {
            diffuse(dt);
        }
    }
}

void Ball::interact(std::vector<MT*> mts,float dt)
{
    if (attached)
    {
        move_along(dt);
    }
    else
    {
        iterate_mts(mts, dt);
    }

}