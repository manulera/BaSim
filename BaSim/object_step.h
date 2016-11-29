void Object::diffuse(float dt)
{
    // calibrate diffusion, I will have to include also the mass at some point
    float alpha = sqrt( 2 * diff * dt );
    Vector2 unit = Vector2(srand(),srand());
    unit.normalize(alpha);
    position += unit;
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