int within(Ball* balli, MT* mti , float* distval)

//    /* Function that determines if a motor is close to a MT by a distance of 'range'.
//        + Returns 0 if its further than range
//        + Returns 1 if its in range from the minus end
//        + Returns 2 if its in range from the plus end
//        + Returns 3 if its in range from the body of the MT
//     */
{
    // This is based on the notes of the notebook
    
    float a = dist(balli->x,balli->y,mti->x,mti->y); //Distance from the minus end
    float b = dist(balli->x,balli->y,mti->xp(),mti->yp()); //Distance from the plus end
    float c = mti->length;
    float h = sqrt(a*a-pow((a*a-b*b+c*c)/2/c,2));
    if ((b*b+c*c<a*a) && (a>=b)) // Plus end
    {*distval = dist(balli->x,balli->y,mti->xp(),mti->yp());
        return (*distval < *(balli->bind_range))*2;}
    else if ((a*a+c*c<b*b) && (a<=b)) // Minus end
    {*distval = dist(balli->x,balli->y,mti->x+mti->x,mti->y);
        return (*distval < *(balli->bind_range))*1;}
    else //Body of the microtubule
    {*distval = h;
        return (*distval < *(balli->bind_range))*3;}
}

void move_along(Ball* balli,MT* mti)
{
    // dist0 is the distance that the motors travels in dt
    float dist0 = *(balli->speed) * dt;
    balli->x+=dist0*cos(mti->orientation);
    balli->y+=dist0*sin(mti->orientation);
    if (dist(balli->x,balli->y,mti->x,mti->y)>mti->length||dist(balli->x,balli->y,mti->xp(),mti->yp())>mti->length)
        balli->attached=false;
}

void bind(Ball* balli, MT* mti, int where, float distval)
{
    glLineWidth(1);
    glBegin(GL_LINES);
    {
        //glVertex2f(x/xBound, y/yBound);
        if (where==1) //Bind to minus end
        {
            balli->x=mti->x;
            balli->y=mti->y;
        }
        else if (where==2) //Bind to plus end
        {
            balli->x=mti->xp();
            balli->y=mti->yp();
            
        }
        else if (where==3) //Bind to body
        {
            float a = dist(balli->x,balli->y,mti->x,mti->y); //Distance from the minus end
            float dist0 = sqrt(std::abs(a*a-distval*distval)); // There are cases where this is negative
            balli->x=mti->x+dist0*cos(mti->orientation);
            balli->y=mti->y+dist0*sin(mti->orientation);
        }
        //glVertex2f(x/xBound, y/yBound);
    }
    glEnd();
}

void interaction(Ball* balli,MT* mti, int i_m)
{
    if (!balli->attached)
    {
        float distval;
        int wherebind = within(balli,mti,&distval);
        std::cout << wherebind << std::endl;

        if (wherebind && rand01()<binding_rate*dt)
        {
            balli->attached=i_m+1;
            bind(balli, mti ,wherebind, distval);
        }
        else
        {
            balli->diffuse();
        }
    }
    else if (balli->attached - 1 ==i_m)
    {
        move_along(balli,mti);
    }
    
}
