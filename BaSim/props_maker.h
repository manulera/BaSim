Props* makeProps(std::string (&keys) [3], std::string prop_val)
{
    std::cout << prop_val << std::endl;
    if (keys[1]=="ball") return new Ballprops(keys,prop_val);
    if (keys[1]=="MT") return new MTprops(keys,prop_val);
    return 0;
}

// This one is for when we are reading the file, might not be the best solution, but so far it works
Props* makeProps(std::string input)
{
    using namespace std;
    stringstream ss(input);
    string chunk;
    string keys[3];
    string pairs;
    size_t ind;
    
    getline(ss, chunk);
    ind=chunk.find(": ");
    keys[2]=chunk.substr(ind+2);
    
    getline(ss, chunk);
    ind=chunk.find(": ");
    keys[1]=chunk.substr(ind+2);
    
    while (getline(ss,chunk))
    {
        ind=chunk.find(": ");
        pairs += chunk.substr(0,ind) + "," + chunk.substr(ind+2)+",";
        cout << pairs << endl;
    }
    return makeProps(keys, pairs);
}