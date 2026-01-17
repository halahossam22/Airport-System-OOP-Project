#include "administrator.h"
#include "booking_system.h" 
#include "user.h"
#include "flight.h"
#include <iostream>
using namespace std;
administrator::administrator()
{
	role = "admin";
}

administrator::administrator(string n, string p)
{
	username = n;
	userpassword = p;
	role = "admin";
}

void administrator::addnewuser(booking_system& b, user* u)
{
	for (int i = 0; i < b.usercount; i++) {
		if (b.getuser(i)->getname() == u->getname() && b.getuser(i)->getpass() == u->getpass()) {
			cout << "Error: User [" << u->getname() << "] with this password already exists in the system!" << endl;
			delete u;
			return;
		}
	}
	b.adduser(u);
	b.addlog("Admin [" + getname() + "] added a new user: " + u->getname());
}
void administrator::addnewflight(booking_system& b, flight* f)
{
	for (int i = 0; i < b.flightcount; i++) {
		if (b.getflight(i)->getflightnum() == f->getflightnum()) {
			cout << "Error: Flight number [" << f->getflightnum() << "] already exists in the system!" << endl;
			delete f;
			return;
		}
	}
	b.addflight(f);
	b.addlog("Admin [" + getname() + "] added a new flight: " + f->getflightnum());
}
void administrator::monitorsystem(booking_system& b)
{
	cout << "admin " << getname() << " is checking logs:" << endl;
	b.viewsystemlogs();
}

string administrator::getrole()
{

	return role;
}
