Object* makeObject(Props& props)
{
    std::cout << props.type<< std::endl;
    Props* a = &props;
    if (props.type=="ball") return new Object(props);
    return 0;
    Props* p;
    Object* ob = new Object(*p);

}