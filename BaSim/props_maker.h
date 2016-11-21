Props* makeProps(std::string (&keys) [3], std::string prop_val)
{
    if (keys[1]=="ball") return new Ballprops(keys,prop_val);
    if (keys[1]=="MT") return new MTprops(keys,prop_val);
    return 0;
}