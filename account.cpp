#include "account.h"
using namespace std;

void Account::deposit(int val) {
	amount += val;
}

void Account::withdraw(int val) {
	amount -= val;
}

string Account::get_id() {
	return id;
}

int Account::get_deposit() {
	return amount;
}
