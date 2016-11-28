
void regiondrawer{
for (float i=-1; i<=1; i+=0.01)
{for (float j=-1; j<=1; j+=0.01)
{
    float d= 10;
    int type = 0;
    float a = dist(i*xBound,j*yBound,mt.x,mt.y);//Distance from the minus end
    float b = dist(i*xBound,j*yBound,mt.x+mt.length,mt.y);//Distance from the plus end
    float c = mt.length;
    float h = sqrt(a*a-pow((a*a-b*b+c*c)/2/c,2));
    
    if ((b*b+c*c<a*a) && (a>=b)) // Plus end
    {d = dist(i*xBound,j*yBound,mt.x+mt.length,mt.y);
        type = 1;}
    else if ((a*a+c*c<b*b) && (a<=b)) // Minus end
    {d = dist(i*xBound,j*yBound,mt.x,mt.y);
        type = 2;}
    else
    {d = h; type = 3;}
    
    if (d<100){
        glBegin(GL_POINTS);
        {
            if (type==1) glColor3f(1.0, 0.0, 0.0);
                else if (type==2) glColor3f(0.0, 1.0, 0.0);
                    else if (type==3) glColor3f(0.0, 1.0, 1.0);
                        glVertex2f(i,j);
                        }
        glEnd();}
    
    //MT
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(mt.x/xBound, mt.y/yBound);
        glVertex2f((mt.x+mt.length)/xBound, mt.y/yBound);
    }
    glEnd();
    
}}
}