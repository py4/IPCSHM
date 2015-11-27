#ifndef CORE_H_
#define CORE_H_

#include <sys/types.h>
class Transaction;
class SharedMem;

class Core {
	public:
		Core();
		~Core();
		void init_mem();
		void start();
		void handle_requests();

	private:
		void init_arr_count();
		void init_arr();
		SharedMem* sm;
};
#endif
