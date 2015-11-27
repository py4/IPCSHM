#include "utils.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <cstdio>
using namespace std;

string get_content_except_last(string file_name, string* hash) {
	string content;
	string line;
	ifstream in(file_name.c_str());
	while(getline(in, line)) {
		if(line[0] != '#')
			content += line+'\n';		
		else
			*hash = line.substr(2);
	}
	return content.substr(0, content.size()-1);
}

string get_sha1(string file_name, string* hash) {
	string content = get_content_except_last(file_name,hash);
	unsigned char* ibuf = new unsigned char[content.length()];
	for(int i = 0; i < content.length(); i++)
		ibuf[i] = 0;
	memcpy(ibuf, content.c_str(), content.length());
	unsigned char obuf[20];
	SHA1(ibuf, strlen(content.c_str()), obuf);
	return string(reinterpret_cast<char*>(obuf));
}

vector<string> tokenize(string str) {
	vector<string> result;
	string token;
	stringstream ss(str);
	while(getline(ss, token, ' '))
		result.push_back(token);
	return result;
}


/*int main() {
	string given_hash, sha1_hash;
	sha1_hash = get_sha1("inputs/3",&given_hash);
	cout << sha1_hash;
} */
