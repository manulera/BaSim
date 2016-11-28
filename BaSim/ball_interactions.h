
int Ball::within(MT* mti , float* distval)

//    /* Function that determines if a motor is close to a MT by a distance of 'range'.
//        + Returns 0 if its further than range
//        + Returns 1 if its in range from the minus end
//        + Returns 2 if its in range from the plus end
//        + Returns 3 if its in range from the body of the MT
//        + distval is asigned the value of the square of the distance
//     */
{
    // This is based on the notes of the notebook
    
    float a = position.distSqr(mti->position); //Distance_sqrd from the minus end
    float b = position.distSqr(mti->plus_end()); //Distance_sqrd from the plus end
    float c = mti->length;
    //float h = a- ((a-b+c*c)/2/c) * ((a-b+c*c)/2/c);
    
    if ((b+c*c<a) && (a>=b)) // Plus end
    {
        *distval = b;
        return (*distval < *(bind_range))*2;
    }
    else if ((a+c*c<b) && (a<=b)) // Minus end
    {
        *distval = a;
        return (*distval < *(bind_range))*1;
    }
    else //Body of the microtubule
    {
        *distval = a- ((a-b+c*c)/2/c) * ((a-b+c*c)/2/c); // The h value explained on the notebook
        return (*distval < *(bind_range))*3;}
}

void Ball::move_along(float dt)
{
    // The distance that the motors travels in dt
    position += attached->orientation * *speed * dt;
    
    if (position.distSqr(attached->position) > attached->length * attached->length ||
        position.distSqr(attached->plus_end()) > attached->length * attached->length)
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
// BaSim_2
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
// BaSim_1
//void Ball::iterate_mts(std::vector<MT*> mts,float dt)
//{
//       float distval;
//       for (int i = 0; i<mts.size(); i++)
//            {
//                int wherebind = within(mts.at(i),&distval);
//                if (wherebind && rand01()<*bind_rate*dt)
//                    {
//                        bind(mts.at(i),wherebind, distval);
//                    }
//                else
//                    {
//                        diffuse(dt);
//                    }
//            }
//}
//
//void Ball::interact(std::vector<MT*> mts,float dt)
//{
//    if (attached)
//        {
//            move_along(dt);
//        }
//    else
//        {
//            iterate_mts(mts, dt);
//        }
//}

//// BaSim_Old
//void Ball::iterate_mts(std::vector<MT*> mts,float dt)
//{
//    float distval;
//    for (int i = 0; i<mts.size(); i++)
//    {
//        if (attached)
//        {
//            if (attached_id==mts.at(i)->identifier) move_along(dt);
//        }
//        else
//        {
//            int wherebind = within(mts.at(i),&distval);
//            if (wherebind && rand01()<*bind_rate*dt)
//            {
//                bind(mts.at(i),wherebind, distval);
//            }
//            else
//            {
//                diffuse(dt);
//            }
//        }
//    }
//}
//
//void Ball::interact(std::vector<MT*> mts,float dt)
//{
//    iterate_mts(mts, dt);
//}
//

















