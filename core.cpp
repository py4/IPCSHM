#include "core.h"
#include "shared_mem.h"
#include <ctime>
#include "bank.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <cstdio>
#include <string>
#include <iostream>
#include "transaction.h"
#include "validator.h"
#include "applier.h"
#include <unistd.h>

using namespace std;

Core::Core() {
	sm = new SharedMem(true);
}

Core::~Core() {
	delete sm;
}

void Core::start() {
	Validator* validator_a = new Validator();
	Validator* validator_b = new Validator();
	Applier* applier = new Applier();

	if(fork() == 0) {
		cout << "[Core] forked a validator" << endl;
		validator_a->monitor();
	}
	else {
		if(fork() == 0) {
			cout << "[Core] forked a validator" << endl;
			validator_b->monitor();
		}
		else {
			if(fork() == 0) {
				cout << "[Core] forked an applier" << endl;
				applier->monitor();
			}
			else
				this->handle_requests();
		}
	}
}

void Core::handle_requests() {
	cout << "[Core] start handling requests" << endl;
	string file_name;
	while(cin >> file_name) {
		
		file_name.copy(sm->arr[*(sm->arr_count)].file_name, file_name.length());
		sm->arr[*(sm->arr_count)].file_name[file_name.length()] = '\0';
		sm->arr[*(sm->arr_count)].flag = UNCHECKED;
		sm->arr[*(sm->arr_count)].timestamp = time(0);
		if(sem_init(&(sm->arr[*(sm->arr_count)].sem), 1, 1) < 0)
			perror("sem_init");
		(*(sm->arr_count))++;
	}
}
