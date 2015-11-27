#include "validator.h"
#include "shared_mem.h"
#include "transaction.h"
#include <iostream>
#include <cstdio>
#include "utils.h"
using namespace std;

Validator::Validator() {
	sm = new SharedMem(false);
}

Validator::~Validator() {
	sm->detach();
	delete sm;
}

void Validator::monitor() {
	cout << "[Validator] started monitoring" << endl;
	while(true) {
		for(int i = 0; i < *(sm->arr_count); i++) {
			if(sem_trywait(&sm->arr[i].sem) == 0) {
				if(sm->arr[i].flag == UNCHECKED and (time(0) - sm->arr[i].timestamp) > 0) {
					sm->arr[i].timestamp = time(0);
					if(sem_post(&sm->arr[i].sem) < 0)
						perror("sem_post");
					cout << "[Validator] found something to consume!" << endl;
					validate(i);
				} else
					if(sem_post(&sm->arr[i].sem) < 0)
						perror("sem_post");
			}
		}
	}
}

void Validator::validate(int i) {
	string given_hash, sha1_hash;
	sha1_hash = get_sha1(sm->arr[i].file_name, &given_hash);
	if(sem_wait(&sm->arr[i].sem) < 0)
		perror("sem_wait");

	cout << "[Validator] updating " << sm->arr[i].file_name << endl;
	
	sm->arr[i].flag = (sha1_hash == given_hash ? VALID : INVALID);

	cout << "[Validator][" << i << "] sha1_hash:  " << sha1_hash << endl;
	cout << "[Validator][" << i << "] given_hash:  " << given_hash << endl;
	cout << "[Validator][" << i << "] valid:  " << (sm->arr[i].flag == VALID) << endl;
	sm->arr[i].timestamp = time(0);
	if(sem_post(&sm->arr[i].sem) < 0)
		perror("sem_post");
}
