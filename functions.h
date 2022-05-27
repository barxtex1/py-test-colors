#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "defs.h"

std::vector<std::string> split(const std::string& str, char seperator);
std::string decToHexa(int n);
int HexToDec(char num[]);
std::string hex2rgba(const std::string &hex_);
std::string rgba2rgb(const std::string &rgba);
std::string rgba2hsl(const std::string &rgba, const bool &check);
std::string rgba2hex(const std::string &rgba);


#endif // FUNCTIONS_H
