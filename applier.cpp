#include "applier.h"
#include "bank.h"
#include "shared_mem.h"
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"
#include <cstdlib>
using namespace std;

Applier::Applier() {
	bank = new Bank;
	sm = new SharedMem(false);
}

Applier::~Applier() {
	delete bank;
	sm->detach();
	delete sm;
}

void Applier::monitor() {
	cout << "Started monitoring" << endl;
	while(true) {
		for(int i = 0; i < *(sm->arr_count); i++) {
			if(sm->arr[i].flag == VALID)
				apply(sm->arr[i].file_name);
		}
	}
}

void Applier::apply(string file_name) {
	ifstream in(file_name.c_str());
	string line;
	while(getline(in,line)) {
		vector<string> tokens = tokenize(line);
		if(tokens[0] == "create")
			bank->create_account(tokens[1]);
		else if(tokens[0] == "deposit")
			bank->deposit(tokens[1], atoi(tokens[2].c_str()));
		else if(tokens[0] == "withdraw")
			bank->withdraw(tokens[1], atoi(tokens[2].c_str()));
		else if(tokens[0] == "move")
			bank->move(tokens[1], tokens[2], atoi(tokens[3].c_str()));
	}
}



