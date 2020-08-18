#pragma once
#include <string>
#include <fstream>
#include <sstream>
static std::string readStrFromFile(const std::string &filename)
{
    using namespace std;
    ifstream ifile(filename);
    ostringstream buf;
    char c;
    while (buf && ifile.get(c))
        buf.put(c);
    ifile.close();
    return buf.str();
}