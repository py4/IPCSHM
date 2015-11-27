#ifndef APPLIER_H_
#define APPLIER_H_

#include "transaction.h"
class Bank;
class SharedMem;

class Applier {

	public:
		Applier();
		~Applier();		
		void monitor();

private:
		void apply(std::string);
		Bank* bank;
		SharedMem* sm;
};
#endif
