
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
    
    float a = position.distSqr(mti->minus_end()); //Distance_sqrd from the minus end
    float b = position.distSqr(mti->plus_end()); //Distance_sqrd from the plus end
    float c = mti->length;
    
    if ((b+c*c<a) && (a>=b)) // Plus end
    {
        *distval = b;
        return (*distval < props->bind_range * props->bind_range)*2;
    }
    else if ((a+c*c<b) && (a<=b)) // Minus end
    {
        *distval = a;
        
        return (*distval < props->bind_range * props->bind_range)*1;
    }
    else //Body of the microtubule
    {
        // distval corresponds to the h value explained on the notebook, height calculated with Heron's theorem
        float term = (a-b+c*c)/2/c;
        *distval = a - term * term;
        return (*distval < props->bind_range * props->bind_range)*3;}
}

void Ball::move_along(float dt)
{
    // The distance that the motors travels in dt
    if (props->unbind_rate * dt > rand01())
    {
        unbind();
        return;
    }
    tubref += props->speed * dt / attached->length * stall;
    if (tubref<-0.5||tubref>0.5)
    {
        position = attached->position + attached->orientation * attached->length * tubref;
        unbind();
        return;
    }
    if (tethered)
    {
        pull_mt(dt);
    }
    position = attached->position + attached->orientation * attached->length * tubref;
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
            tubref = -0.5;
        }
        else if (where==2) //Bind to plus end
        {
            tubref = 0.5;
        }
        else if (where==3) //Bind to body
        {
            // Vector from the center to the ball * unitary vector of the orientation
            tubref = (position - mti->position) * mti->orientation / mti->length;
        }
        //glVertex2f(x/xBound, y/yBound);
    }
    //glEnd();
}
// BaSim_2
void Ball::iterate_mts(std::vector<MT*> mts,float dt)
{
    int wherebind;
    float distval;
    for (int i = 0; i<mts.size(); i++)
    {
        if (rand01()< props->bind_rate*8*dt)
        {
            wherebind = within(mts.at(i),&distval);
            if (wherebind && rand01()<0.125)
            {
                bind(mts.at(i),wherebind, distval);
                break; // Wow! I cant believe I didnt have this before, this is definitely the reason why I was getting similar times in clearly more efficient methods
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


void Ball::tether(std::vector<Tether*> tethers)
{
    for (int i = 0; i < tethers.size();i++)
        {
            if (tethers.at(i)->label==tetherlabel)
            {
                tethered = tethers.at(i);
            }
        }
}

void Ball::pull_mt(float dt)
{
    Vector2 f_vect = (tethered->position - position) * tethered->props->force_k  ;
    
    // Stalling force and movement along the fiber axis
    
    float f_norm = f_vect * attached->orientation;
    float shift = f_norm / attached->props->mobility;
    attached->position += attached->orientation * shift * dt ;
    stall = 1 - f_norm/ props->stall_force;
    
    // Net movement and torsion
    
    // Displacement of the mass center
    attached->position += f_vect/attached->props->mobility * dt;
    // Rotation
    float ang_acc = vecProd(attached->orientation*attached->length*tubref,f_vect) * attached->inertia();
    float ang_disp = ang_acc * dt * dt / 2 ;
    std::cout << ang_disp << std::endl;
    attached->orientation.rotate(ang_disp*0.00001);
}


void Ball::unbind()
{
    tubref = 0.0;
    attached=nullptr;
    attached_id=0;
}










