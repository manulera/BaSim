#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

std::string ini = "h2345ello  bro   sup";
std::stringstream ss(ini);

#ifdef MAIN

int main()
{
    char a = ss.get();
    std::cout << a <<std::endl;
    a = ss.peek();
    std::cout << a <<std::endl;
    
    int ptr;
    // This transmission from the ss to ptr also causes the position of the string stream to move, this is the whole point of this method!
    ss >> ptr;
    std::cout << ptr <<std::endl;
    char c;
    ss.get(c);
    std::cout << c <<std::endl;
    
    std::cout << ss.str() <<std::endl;
    
    return 0;
}
#endif
