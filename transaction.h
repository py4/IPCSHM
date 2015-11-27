#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <ctime>
#include <semaphore.h>

enum Flag { VALID, INVALID, UNCHECKED };

typedef struct Transaction {
	std::string file_name;
	Flag flag;
	std::time_t timestamp;
	sem_t sem;	
} Transaction;

#endif
