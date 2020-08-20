#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
static std::string readStrFromFile(const std::string &filename)
{
    using namespace std;
    ifstream ifile(filename);
    if (ifile)
    {
        ostringstream buf;
        char c;
        while (buf && ifile.get(c))
            buf.put(c);
        ifile.close();
        return buf.str();
    }
    else
    {
        cerr << "cannot open the file \"" << filename << "\"" << endl;
        return "";
    }
}