#include <iostream>
#include <fstream>

void cpp_get_saying(char * isay)
{
    std::ifstream infile; 
    infile.open("./isay.txt");
    infile >> isay;
    infile.close(); 
}