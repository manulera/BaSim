

float dist(float x1, float y1, float x2, float y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}


class Ball{
public:
    
    float range, speed;
    float x,y;
    int attached;
    
    void reset() {
        speed = motor_speed;
        x=(rand01()*0.5+0.5)*xBound;
        y=srand()*yBound;
        attached = 0;
    }
    
    Ball()
    {
        reset();
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
            if (wherebind && rand01()>(1-binding_rate)*dt)
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
        }
        boundary();
    }

    void diffuse()
    {
        // calibrate diffusion:
        float alpha = sqrt( 2 * diff * dt );
        x+=alpha*srand()*dt;
        y+=alpha*srand()*dt;
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
        
        float a = dist(x,y,mti.posx,mti.posy); //Distance from the minus end
        float b = dist(x,y,mti.posxp(),mti.posyp()); //Distance from the plus end
        float c = mti.length;
        float h = sqrt(a*a-pow((a*a-b*b+c*c)/2/c,2));
        
        if ((b*b+c*c<a*a) && (a>=b)) // Plus end
            {*distval = dist(x,y,mti.posxp(),mti.posyp());
             return (*distval<range)*2;}
        else if ((a*a+c*c<b*b) && (a<=b)) // Minus end
            {*distval = dist(x,y,mti.posx+mti.posx,mti.posy);
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
        glVertex2f(x/xBound, y/yBound);
        if (where==1) //Bind to minus end
        {
            x=mti.posx;
            y=mti.posy;
        }
        else if (where==2) //Bind to plus end
        {
            x=mti.posxp();
            y=mti.posyp();

        }
        else if (where==3) //Bind to body
        {
            int a = dist(x,y,mti.posx,mti.posy); //Distance from the minus end
            int dist0 = sqrt(std::abs(a*a-distval*distval)); // There are cases where this is negative
            x=mti.posx+dist0*cos(mti.orientation);
            y=mti.posy+dist0*sin(mti.orientation);
        }
        glVertex2f(x/xBound, y/yBound);
        }
        glEnd();
    }
    
    void move(MT mti)
    {
        float dist0=speed*dt;
        x+=dist0*cos(mti.orientation);
        y+=dist0*sin(mti.orientation);
        if (dist(x,y,mti.posx,mti.posy)>mti.length||dist(x,y,mti.posxp(),mti.posyp())>mti.length)
            attached=false;
    }
};


