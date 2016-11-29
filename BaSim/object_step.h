void Object::diffuse(float dt)
{
    // calibrate diffusion, I will have to include also the mass at some point
    Vector2 unit = Vector2(srand(),srand());
    unit.normalize(sqrt( 2 * diff * dt ));
    position += unit;
    boundary();
}

void Object::boundary()
{
    if (position.XX>xBound)
        position.XX=2*xBound-position.XX;
    if (position.YY>yBound)
        position.YY=2*yBound-position.YY;
    if (position.XX<-xBound)
        position.XX=-2*xBound-position.XX;
    if (position.YY<-yBound)
        position.YY=-2*yBound-position.YY;
}