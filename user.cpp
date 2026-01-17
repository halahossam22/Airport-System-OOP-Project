#include "user.h"
#include "booking_system.h"
#include<iostream>
#include<random>
using namespace std;
int booking_system::idcount = 1000;
int booking_system::usercount = 0;
int booking_system::flightcount = 0;
int payment::transactionCounter = 5000;
user::user()
{
}
string user::getname()
{
	return username;
}

string user::getpass()const
{
	return userpassword;
}

bool user::login(string inputname, string inputpassword, booking_system& b)
{
	bool found = false;
	for (int i = 0;i < b.usercount;i++) {
		if (b.alluser[i]->getname() == inputname) {
			if (b.alluser[i]->isvalidpassword(inputpassword)) {
				cout << b.alluser[i] << endl;
				found = true;
				return found;
			}
		}
	}
	if (!found) {
		cout << "invaild name or password";
	}
	return found;
}
void user::updateprofile(string inputname, string inputpassword)
{
	username = inputname;
	userpassword = inputpassword;
}
bool user::isvalidpassword(string inputpassword) const
{
	if (inputpassword.empty()) {
		return false;
	}
	if (inputpassword.length() < 8) {
		return false;
	}
	return true;
}
ostream& operator<<(ostream& out, const user* u)
{
	if (u != nullptr) {
		out << "User Profile: [Name: " << u->username << "]";
	}
	return out;
}


