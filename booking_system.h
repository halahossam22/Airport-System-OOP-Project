#pragma once
#include "user.h"
#include "flight.h"
#include "booking.h"
#include "payment.h"
class booking_system {
	payment* p;
	flight* f;
	user** alluser;
	flight** allflight;
	booking* mybookings;
	int maxuser, maxflight;
	int logcount;
	string systemlogs[500];
public:
	booking_system();
	friend class agent;
	friend class user;
	static int usercount, flightcount, idcount, bookingcount;
	booking_system(int usize, int fsize);
	void save_data();
	void load_data();
	void adduser(user* u);
	void addflight(flight* f);
	flight* getflight(int index);
	user* getuser(int index);
	void show_allflights();
	void bookflight(user* u, flight* f, string paydate, string paymethod);
	void addlog(string message);
	void viewsystemlogs();
	static int getnextid();
	static int getid();
	~booking_system();
};