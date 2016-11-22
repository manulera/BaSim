void Object::diffuse()
{
    // calibrate diffusion, I will have to include also the mass at some point
    float alpha = sqrt( 2 * diff * sim.dt );
    x+=alpha*srand();
    y+=alpha*srand();
}

void Object::boundary()
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