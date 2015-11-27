#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <ctime>
#include <semaphore.h>

#define MAX_FILE_NAME_SIZE 50

enum Flag { VALID, INVALID, UNCHECKED, CHECKED };

typedef struct Transaction {
	//std::string file_name;
	char file_name[MAX_FILE_NAME_SIZE];
	Flag flag;
	std::time_t timestamp;
	sem_t sem;	
} Transaction;

#endif
