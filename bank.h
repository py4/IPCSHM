#ifndef BANK_H_
#define BANKH_H_

#include <vector>
#include <string>

class Account;

class Bank {
	public:
		~Bank();
		void create_account(std::string);
		void deposit(std::string,int);
		void withdraw(std::string,int);
		void move(std::string,std::string,int);

	private:
		Account* get_account(std::string);
		std::vector < Account* > accounts;
};

#endif
