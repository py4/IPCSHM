#ifndef SHARED_MEM_H_
#define SHARED_MEM_H_

#include <sys/types.h>

#define ARRC_SHM_KEY 123
#define ARR_SHM_KEY 124
#define ARRC_SHM_SIZE 4
#define ARR_SHM_SIZE 1000

class Transaction;
int get_mem(key_t, size_t, bool);
void* attach_mem(int);

class SharedMem {
	
	public:
		SharedMem(bool);
		void detach();
		void die();

		int arr_count_shm_id;
		int arr_shm_id;
		Transaction* arr;
		int* arr_count;

};

#endif
