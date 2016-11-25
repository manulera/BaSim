// Inspired from the file in the cytosim webpage


#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

typedef double real;

/// possible error messages:
enum { GOOD_READ, BAD_READ, SHORT_READ, NO_KEY, NO_MATCH, NO_EQUAL };

/// report the error type in Human readable text
std::string errorMessage(int code)
{
    switch( code )
    {
        case  GOOD_READ:  return "no error";
        case   BAD_READ:  return "syntax error";
        case SHORT_READ:  return "unexpected entry";
        case     NO_KEY:  return "missing parameter";
        case   NO_MATCH:  return "unknown parameter";
        case   NO_EQUAL:  return "missing equal sign";
        default:          return "unknown error";
    }
}

void printfile(std::istream& is)
{
    auto index = is.tellg();
    std::cout << "Whole file:\n"<<is.rdbuf() << std::endl;
    is.seekg(index);
}
/// this prints the line of the input stream, indicating the positions in another line below
void showPosition(std::ostream& os, std::istream& is, std::streampos beg, std::streampos end)
{
    if ( !is.good() )
        is.clear();
    
    // count number of lines:
    is.seekg(0, std::ios::beg);
    unsigned cnt = 0;
    std::string line;
    
    std::streampos isp;
    while ( is.good()  &&  is.tellg() <= beg )
    {
        isp = is.tellg();
        std::getline(is, line);
        ++cnt;
    }
    
    // print line number:
    os << std::setw(8) << cnt << " |";
    
    // print entire line:
    for( int i = 0; i < line.size(); ++i )
    {
        char c = line[i];
        if ( isspace(c) )
            os << " ";
        else if ( isprint(c) )
            os << c;
    }
    
    os << "\n          ";
    
    is.seekg(isp, std::ios::beg);
    while ( is.tellg() < beg )
    {
        is.get();
        os << " ";
    }
    
    while ( is.tellg() < end )
    {
        is.get();
        os << "^";
    }
    os << std::endl;
}


/// report an error
void badValue(std::string const& msg)
{
    std::cerr << "Error: " << msg << std::endl;
    exit(EXIT_FAILURE);
}

// A Parser class, can be useful to simplify the functions a lot
class Parser{
public:
    std::istream *is;
    std::streampos pos;
    std::string word;
    std::string keys[3];
    std::string prop_val;
    int parse();
    int parseOne();
    int get3keys();
    int get1key(bool);
    bool skip_spaces();
    std::string readkey(bool);
    int read1();
    void pass_values();

    
    void readfile(std::istream& input_is)
    {
        is = &input_is;
        if ( is->good() )
        {
            
            parse();
        }
        else
            std::cerr << "Stream is empty!"<< std::endl;
    }
    
    // I dont know if this constructor will work
//    Parser(std::string const& str)
//    {
//        std::istringstream is(str);
//        parse();
//    }
};


bool Parser::skip_spaces()
{
    int c = is->peek();
    while ( isspace(c) )
    {
        is->get();
        c = is->peek();
    }
    pos = is->tellg();
    if ( c == EOF )
        return 1;
    else
        return 0;
    
}

std::string Parser::readkey(bool isval)
{
    // isval is a boolean that is one in case that the key that we are reading corresponds to a value. In that case it can start with a number, otherwise, if it is either the name of a property or set/new, etc. it should start with a
    std::string res;
    int c = is->get();
    // name should start with alpha:
    if (!isval && !isalpha(c) )
        return res;
    // accept alpha nums and underscore and dots(representing the comma for numbers)
    do
    {
        res.push_back((char)c);
        c = is->get();
    } while ( isalnum(c) || c == '_' || c=='.');
    is->putback(c);
    return res;
}

int Parser::get3keys()
{
    for (int i=0; i<3; i++)
    {
        if (skip_spaces()==1)
            return 1;
        keys[i] = readkey(1);
    }
    return 0;
}

int Parser::get1key(bool isval)
{
    if (skip_spaces()==1)
        return 1;
    word = readkey(isval);
    return 0;
}

void Parser::pass_values()
{
    if (keys[0]=="set")
    {
        sim.add_prop(*makeProps(keys, prop_val));
    }
    if (keys[0]=="new")
    {
        sim.add_object(keys, prop_val);
    }
    prop_val.erase();
}

/// read values
int Parser::read1()
{
    // If the end of the file is reached
    auto index = is->tellg();
    //if (get1key(1)) return GOOD_READ;
    get1key(1);
    // Some "set" statements don't have to include the key brackets with info maybe, they can be simply initialized with default values, and then some properties specified in the "new" statement
    
    if (word != "{")
    {
        is->seekg(index);
        pass_values();
        return GOOD_READ;
    }
    while (true)
    {
        if (get1key(1)) return GOOD_READ;
        
        if (word=="}")
        {
            prop_val.pop_back();
            break;
        }
        
        prop_val.append(word);
        
        if (get1key(1)) return GOOD_READ;
        
        if (word != "=") return NO_EQUAL;
        prop_val.append(",");
        
        if (get1key(1)) return GOOD_READ;
        prop_val.append(word);
        prop_val.append(",");
    }
    pass_values();
    return GOOD_READ;
}

/// read one assignement from an input stream
int Parser::parseOne()
{
    
    if (get3keys())
    {
        return GOOD_READ;
    }
    return read1();
}


/// read assignements from an input stream
int Parser::parse()
{
    
    int e = GOOD_READ;
    while ( is->good() )
    {
        pos = is->tellg();
        
        e = parseOne();
        if ( e != GOOD_READ )
        {
            std::cerr << errorMessage(e) << std::endl;
            showPosition(std::cerr, *is, pos, is->tellg());
            //stop at the first error:
            break;
        }
    }
    return e;
}