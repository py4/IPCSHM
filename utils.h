#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>

std::string get_content_except_last(std::string, std::string*);
std::string get_sha1(std::string, std::string*);
std::vector <std::string> tokenize(std::string);
#endif
