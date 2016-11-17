//
//  parameters.cc
//
//  This code shows how to use C++ templates to parse parameters,
//  of any type, either from a text file or from the command line.
//  The syntax that is understood is:
//  name = value
//  where 'name' should correspond to a predefined list of parameters,
//  hardcoded during compilation.
//  The class Parameters encapsulates all the parameters.
//
//  To compile this file: g++ -D MAIN parameters.cc -o param
//
//  Created by Francois Nedelec on 03/04/2014.
//
//
// Copyright (C) 2014 Francois Nedelec
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details:
// <http://www.gnu.org/licenses/>.
//
// ------------------------------------------------------------------------------


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

/**
 Reads the identifier of a variable.
 This is necessarily a token starting with an alphabetical character,
 and containing alpha-numeric characters or the underscore character ('_').
 */


std::string readKey(std::istream& is, bool isval)
{
    // isval is a boolean that is one in case that the key that we are reading corresponds to a value. In that case it can start with a number, otherwise, if it is either the name of a property or set/new, etc. it should start with a
    std::string res;
    int c = is.get();
    
    // name should start with alpha:
    if (!isval && !isalpha(c) )
        return res;
    
    // accept alpha nums and underscore and dots(for numbers)
    do
    {
        res.push_back((char)c);
        c = is.get();
    } while ( isalnum(c) || c == '_' || c=='.');
    
    is.putback(c);
    return res;
}


bool skip_spaces(std::istream& is, std::streampos& pos)
{
    int c = is.peek();
    while ( isspace(c) )
    {
        is.get();
        c = is.peek();
    }
    pos = is.tellg();
    if ( c == EOF )
        return 1;
    else
        return 0;

}

int get3keys(std::istream& is, std::streampos& pos,std::string (&keys)[3])
{
    for (int i=0; i<3; i++)
    {
        if (skip_spaces(is,pos)==1)
            return 1;
        keys[i] = readKey(is,1);
        //std::cout << "One key read: " <<keys[i] << std::endl;
    }
    return 0;
}

int get1key(std::istream& is, std::streampos& pos,std::string& key, bool isval)
{
    if (skip_spaces(is,pos)==1)
        return 1;
    key = readKey(is,isval);
    return 0;
}

int get_sign(std::istream& is, std::streampos& pos,std::string& key)
{
    if (skip_spaces(is,pos)==1)
        return 1;
    key = readKey(is,1);
    return 0;
}


/**
 Reads the value of `ptr` from the input stream `is`
 @return
 GOOD_READ  : the parameter was set correctly
 BAD_READ   : the keys matched but the value could not be read
 SHORT_READ : a value was read, but some data was left over
 */
template<typename T>
int readValue(std::istream& is, T & ptr)
{
    is >> ptr;
    
    if ( is.fail() )
        return BAD_READ;
    
    // skip trailing spaces:
    int c;
    do {
        c = is.get();
        if ( c == EOF || c == '\n' || c == ';' )
            return GOOD_READ;
    } while ( isspace(c) );
    
    return SHORT_READ;
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



/*
 A class to hold a set of Parameters.
 The functions allow to set default values, to read from a file
 or from the command line arguments, and to print values.
 
 The keyword MORE_PARAMETERS indicates where you should add code,
 to add additional parameters
 */
class Parameters
{
    
public:
    
    int  nb_steps;
    real time_step;
    real rate;
    
    /// value derived from `rate` and `time_step`
    real rate_dt;
    
    
    /// initialize
    Parameters()
    {
        clear();
    }
    
    /// set to default values
    void clear()
    {
        nb_steps  = 0;
        time_step = 1;
        rate      = 0;
        //MORE_PARAMETERS
    }
    
    /// report an error
    void badValue(std::string const& msg)
    {
        std::cerr << "Error: " << msg << std::endl;
        exit(EXIT_FAILURE);
    }
    
    /// calculate values that are derived from the primary parameters
    void complete()
    {
        if ( time_step <= 0 )
            badValue("`time_step' should be strictly positive");
        if ( nb_steps < 0 )
            badValue("`nb_steps' should be positive");
        if ( rate < 0 )
            badValue("`rate' should be positive");
        
        rate_dt = rate * time_step;
        //MORE_PARAMETERS
    }
    
    /// print values
    void print(std::ostream& os) const
    {
        os << " nb_steps  = " << nb_steps << std::endl;
        os << " time_step = " << time_step << std::endl;
        os << " rate      = " << rate << std::endl;
        //MORE_PARAMETERS
    }
    Props* prop;
    /// read values
    int read1(std::istream& is, std::streampos& pos, std::string (&keys) [3])
    {
        std::string key;
        if (keys[0] == "set")
        {
            std::string prop_val;

            if (get1key(is, pos, key,1)) return GOOD_READ;
            if (key != "{") return NO_EQUAL;
            
            while (true)
            {
                
                if (get1key(is, pos, key,1)) return GOOD_READ;
                //std::cout<< "key1 is: " << key << std::endl;
                if (key=="}")
                {
                    //std::cout<< "correct break "<< key << std::endl;
                    prop_val.pop_back();
                    break;
                }
                prop_val.append(key);
 
                if (get1key(is, pos, key,1)) return GOOD_READ;
                if (key != "=") return NO_EQUAL;
                prop_val.append(",");
                
                if (get1key(is, pos, key,1)) return GOOD_READ;
                prop_val.append(key);
                prop_val.append(",");
            }
            //std::cout << prop_val << std::endl;
            std::cout << "set is called"<<std::endl;
            
            prop = makeProps(keys, prop_val);
            Props::type;
            Object* aball;
            new Ball(*prop);
            aball->printinfo();
        }
        
        if (keys[0] == "new")
        {
            //new Object()
            //Something needs to be changed here
            //std::cout << keys[2];
     //       object_list.make(keys[2], std::stoi(keys[1]));
        }

        
        //MORE_PARAMETERS
        return GOOD_READ;
    }
    
    /// read values
    int read(std::istream& is, std::string key)
    {
        if ( key == "set" )    return readValue(is, nb_steps);
        if ( key == "time_step" )   return readValue(is, time_step);
        if ( key == "rate" )        return readValue(is, rate);
        //MORE_PARAMETERS
        return NO_MATCH;
    }

    
    
    /// read one assignement from an input stream
    int parseOne(std::istream& is, std::streampos& pos)
    {
        std::string keys[3];
        if (get3keys(is, pos, keys))
        {
            return GOOD_READ;
        }
        //std::cout<< "3 keys read: " << keys[0] << keys[1] << keys[2] << std::endl;
        
        return read1(is,pos, keys);
    }
    
    
    /// read assignements from an input stream
    int parse(std::istream& is)
    {
        int e = GOOD_READ;
        std::streampos pos;
        while ( is.good() )
        {
            pos = is.tellg();
            e = parseOne(is, pos);
            if ( e != GOOD_READ )
            {
                std::cerr << errorMessage(e) << std::endl;
                showPosition(std::cerr, is, pos, is.tellg());
                //stop at the first error:
                break;
            }
        }
        complete();
        return e;
    }
    
    /// read values contained in a string
    int parse(std::string const& str)
    {
        std::istringstream iss(str);
        return parse(iss);
    }
    
    /// read values from the file called `path`
    int parseFile(const char path[])
    {
        std::ifstream is(path);
        if ( is.good() )
            return parse(is);
        else
            std::cerr << "Cannot open file `" << path << "'" << std::endl;
        return 1;
    }
};


//int main(int argc, char* argv[])
//{
//    Parameters param;
//    param.parseFile("config.bs");
//    for( int i = 1; i < argc; ++i )
//        param.parse(argv[i]);
//    param.print(std::cout);
//    return EXIT_SUCCESS;
//}


