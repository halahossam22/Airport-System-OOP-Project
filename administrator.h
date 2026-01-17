#pragma once
#include "user.h"
#include "flight.h"
class booking_system;
class administrator :public user {
public:
	administrator();
	administrator(string n, string p);
	void addnewuser(booking_system& b, user* u);
	void addnewflight(booking_system& b, flight* f);
	void monitorsystem(booking_system& b);
	string getrole();
};