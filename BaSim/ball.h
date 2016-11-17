



class Ball: public Object{
public:
    bool active;
    float *speed, *bind_rate, *bind_range, *unbind_rate;
    int attached;
    
    
    void shuffle()
    {
        x = srand()*xBound;
        y = srand()*yBound;
    }
    
    void make(Ballprops& props)
    {
        std::cout << "ball maker is reached"<< std::endl;
        active = 1;
        speed = &props.speed;
        x = 0;
        y = 0;
        attached = 0;
        bind_range = &props.bind_range;
        unbind_rate = &props.unbind_rate;
        bind_rate = &props.bind_rate;
        type = &props.type;
        name = &props.name;
    }
    Ball(Props& props): Object(props)
    {
       // make(props);
    }
    
    void printinfo()
    {
        using namespace std;
        cout << "The object "<<  name << "is a " << "with properties:"<<endl;
        cout << "speed: " << speed << "bind_range" << &bind_range << endl;
    }
    
    void boundary()
    {
        if (x>xBound)
            x=2*xBound-x;
        if (y>yBound)
            y=2*yBound-y;
        if (x<-xBound)
            x=-2*xBound-x;
        if (y<-yBound)
            y=-2*yBound-y;

    }

    void step(MT mti,int j)
    {
        if (!attached) //The non attached
        {
            //check if something close and if binding to it.
            float distval = 0.0;
            int wherebind=within(binding_range, mti, &distval);
            if (wherebind && rand01()<binding_rate*dt)
            {
                attached=j+1;
                bind(wherebind, mti , distval);
            }
            else
            {
                diffuse();
            }
        }
        else if (attached==j+1) //The attached, +1 because of 0 indexing of the arrays
        {
            move(mti);
            unbind();
        }
        boundary();
    }

    void diffuse()
    {
        // calibrate diffusion:
        float alpha = sqrt( 2 * diff * dt );
        x+=alpha*srand();
        y+=alpha*srand();
    }
    
    int within(float range, MT mti, float *distval)
    /* Function that determines if a motor is close to a MT by a distance of 'range'.
        + Returns 0 if its further than range
        + Returns 1 if its in range from the minus end
        + Returns 2 if its in range from the plus end
        + Returns 3 if its in range from the body of the MT
     */
    {
        // This is based on the notes of the notebook
        
        float a = dist(x,y,mti.x,mti.y); //Distance from the minus end
        float b = dist(x,y,mti.xp(),mti.yp()); //Distance from the plus end
        float c = mti.length;
        float h = sqrt(a*a-pow((a*a-b*b+c*c)/2/c,2));
        
        if ((b*b+c*c<a*a) && (a>=b)) // Plus end
            {*distval = dist(x,y,mti.xp(),mti.yp());
             return (*distval<range)*2;}
        else if ((a*a+c*c<b*b) && (a<=b)) // Minus end
            {*distval = dist(x,y,mti.x+mti.x,mti.y);
             return (*distval<range)*1;}
        else //Body of the microtubule
            {*distval = h;
            return (*distval<range)*3;}
    }
    
    //Bind to different parts of the MT. This needs to be extended I guess
    void bind(int where, MT mti, float distval)
    {
        glLineWidth(1);
        glBegin(GL_LINES);
        {
        //glVertex2f(x/xBound, y/yBound);
        if (where==1) //Bind to minus end
        {
            x=mti.x;
            y=mti.y;
        }
        else if (where==2) //Bind to plus end
        {
            x=mti.xp();
            y=mti.yp();

        }
        else if (where==3) //Bind to body
        {
            float a = dist(x,y,mti.x,mti.y); //Distance from the minus end
            float dist0 = sqrt(std::abs(a*a-distval*distval)); // There are cases where this is negative
            x=mti.x+dist0*cos(mti.orientation);
            y=mti.y+dist0*sin(mti.orientation);
        }
        //glVertex2f(x/xBound, y/yBound);
        }
        glEnd();
    }
    void unbind()
    {
        if (rand01()<unbinding_rate*dt)
        {
            attached=0;
        }
    }
    void move(MT mti)
    {
        float dist0=*speed * dt;
        x+=dist0*cos(mti.orientation);
        y+=dist0*sin(mti.orientation);
        if (dist(x,y,mti.x,mti.y)>mti.length||dist(x,y,mti.xp(),mti.yp())>mti.length)
            attached=false;
    }
};












