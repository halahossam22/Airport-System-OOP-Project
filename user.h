#pragma once
class booking_system;
#include <fstream>
#include<string>
using namespace std;
class user
{
protected:
	string username, userpassword, role;
public:
	user();
	string getname();
	string getpass()const;
	bool login(string inputname, string inputpassword, booking_system& b);
	void updateprofile(string inputname, string inputpassword);
	virtual string getrole() = 0;
	bool isvalidpassword(string inputpassword) const;
	friend ostream& operator<<(ostream& out, const user* u);

};

