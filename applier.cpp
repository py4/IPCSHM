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
			if(sm->arr[i].flag == VALID) {
				apply(sm->arr[i].file_name);
				sm->arr[i].flag = CHECKED; // no need for semaphore because after being set to VALID, nobody is going to use this
			}
		}
	}
}

void Applier::apply(string file_name) {
	cout << "here" << endl;
	ifstream in(file_name.c_str());
	string line;
	while(getline(in,line)) {
		vector<string> tokens = tokenize(line);
		if(tokens[0] == "Create")
			bank->create_account(tokens[1]);
		else if(tokens[0] == "Deposit")
			bank->deposit(tokens[1], atoi(tokens[2].c_str()));
		else if(tokens[0] == "Withdraw")
			bank->withdraw(tokens[1], atoi(tokens[2].c_str()));
		else if(tokens[0] == "Move")
			bank->move(tokens[1], tokens[2], atoi(tokens[3].c_str()));
		else if(tokens[0] == "End")
			bank->log();
	}
}



