#ifndef STRING_HELPER_HPP
#define STRING_HELPER_HPP

#include <iostream>
#include <vector>

void split(const std::string& s, char c, std::vector<std::string>& v);

std::string trim(std::string &s, char c);

int parseInt(std::string &item);

double parseDouble(std::string &item);

bool parseYN(std::string &yn);

int replaceAll(std::string &text, std::string &pattern, std::string &replacement, std::string &result);

#endif