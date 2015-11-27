#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>

class Account {

	public:
	Account(std::string id) : id(id) {}
	void deposit(int);
	void withdraw(int);
	std::string get_id();
	int get_deposit();

	private:
		int amount;
		std::string id;		
};

#endif
