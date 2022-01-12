#include "string_helper.hpp"
#include <iostream>
#include <vector>

void split(const std::string& s, char c, std::vector<std::string>& v) {
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);

    while (j != std::string::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

std::string trim(std::string &s, char c){
    int stringLength = s.length();
    int substrStart;
    for(substrStart = 0; s[substrStart] == c && substrStart < stringLength; substrStart++){}
    int substrEnd;
    for(substrEnd = stringLength - 1; s[substrEnd] == c && substrEnd >= 0; substrEnd--){}
    return s.substr(substrStart, substrEnd + 1);
}

int parseInt(std::string &item){
    try{
        return std::stoi(item);
    }catch(...){
        // Want to have an logic_error here:
        std::logic_error itemWrongFormat("Der String kann nicht zu Int geparsed werden: " + item);
        throw itemWrongFormat;
    }
}

double parseDouble(std::string &item){
    try{
        return std::stod(item);
    }catch(...){
        // Want to have an logic_error here:
        std::logic_error itemWrongFormat("Der String kann nicht zu Double geparsed werden: " + item);
        throw itemWrongFormat;
    }
}

bool parseYN(std::string &yn){
    if(yn == "y" || yn == "Y"){
        return true;
    }
    if(yn == "n" || yn == "N"){
        return false;
    }
    std::logic_error stringNotYN("Der String ist weder 'y' noch 'n': " + yn);
    throw stringNotYN;
}

int replaceAll(std::string &text, std::string &pattern, std::string &replacement, std::string &result){
    result = std::string(text);
    int patternLength = pattern.size();
    int numberOfReplacements = 0;

    int index = result.find(pattern, index);
    while (index != std::string::npos) {
        result.replace(index, patternLength, replacement);
        index += patternLength;
        
        index = result.find(pattern, index);
        numberOfReplacements++;
    }

    return numberOfReplacements;
}
