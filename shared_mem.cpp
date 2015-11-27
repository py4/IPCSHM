#include "shared_mem.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <cstdio>
#include <iostream>
using namespace std;

int get_mem(key_t shm_key, size_t shm_size, bool owner) {
	int id = shmget(shm_key, shm_size, 0666 | (owner ? IPC_CREAT : 0));
	if(id == -1)
		perror("shmget");
	return id;
}

void* attach_mem(int id) {
	void* ptr = shmat(id, (void*)0, 0);
	if(ptr == (void*)(-1))
		perror("shmat");
	return ptr;
}

SharedMem::SharedMem(bool owner) {
	cout << "[SharedMem] init" << endl;
	arr_count_shm_id = get_mem(ARRC_SHM_KEY, ARRC_SHM_SIZE, owner);
	arr_count = (int*) attach_mem(arr_count_shm_id);
	*(arr_count) = 0;

	arr_shm_id = get_mem(ARR_SHM_KEY, ARR_SHM_SIZE, owner);
	arr = (Transaction*) attach_mem(arr_shm_id);
}

void SharedMem::detach() {
	if(shmdt(arr) < 0)
		perror("shmdt on arr");
	if(shmdt(arr_count) < 0)
		perror("shmdt on arr_count");
	cout << "[SharedMem] Detached!" << endl;
}

void SharedMem::die() {
	if(shmctl(arr_shm_id, IPC_RMID, NULL) < 0)
		perror("shmctl on arr");
	if(shmctl(arr_count_shm_id, IPC_RMID, NULL) < 0)
		perror("shmctl on arr_count");
	cout << "[SharedMem] Detached!" << endl;
}
