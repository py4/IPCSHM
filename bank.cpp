#include "bank.h"
#include "account.h"
#include <iostream>
#include <fstream>
using namespace std;

Bank::~Bank() {
	for(int i = 0; i < accounts.size(); i++)
		delete accounts[i];
}
void Bank::create_account(string account_id) {
	accounts.push_back(new Account(account_id));
}

void Bank::deposit(string account_id, int amount) {
	get_account(account_id)->deposit(amount);
}

void Bank::withdraw(string account_id, int amount) {
	get_account(account_id)->withdraw(amount);
}

void Bank::move(string src_id, string dest_id, int amount) {
	get_account(src_id)->withdraw(amount);
	get_account(dest_id)->deposit(amount);
}

void Bank::log() {
	ofstream fout("logs");
	for(int i = 0; i < accounts.size(); i++)
		fout << "Account " << accounts[i]->get_id() << " deposit :  " << accounts[i]->get_deposit() << endl;
	fout.close();
}

Account* Bank::get_account(string account_id) {
	for(int i = 0; i < accounts.size(); i++)
		if(accounts[i]->get_id() == account_id)
			return accounts[i];
}
