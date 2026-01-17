#include "booking_system.h"
#include <iostream>
#include "administrator.h"
#include "agent.h"
booking_system::booking_system()
{
}

booking_system::booking_system(int usize, int fsize)
{
	maxuser = usize;
	maxflight = fsize;
	usercount = 0;
	flightcount = 0;
	logcount = 0;
	alluser = new user * [maxuser];
	allflight = new flight * [maxflight];
}

void booking_system::save_data() {
	ofstream flightFile("C:\\Users\\HalaH\\OneDrive\\Desktop\\Airport_system1\\Airport_system1\\flights.txt", ios::out);
	for (int i = 0; i < flightcount; i++) {
		int type = (dynamic_cast<internationalflight*>(allflight[i])) ? 2 : 1;

		flightFile << type << " "
			<< allflight[i]->flightnumber << " "
			<< allflight[i]->source << " "
			<< allflight[i]->destination << " "
			<< allflight[i]->getprice() << " "
			<< allflight[i]->getavailableseats();

		if (type == 2) {
			internationalflight* inter = (internationalflight*)allflight[i];
			flightFile << " " << inter->getvisa() << " " << inter->gettax() << " " << inter->getservice();
		}
		flightFile << endl;
	}
	flightFile.close();
	ofstream userFile("C:\\Users\\HalaH\\OneDrive\\Desktop\\Airport_system1\\Airport_system1\\users.txt", ios::out);
	for (int i = 0; i < usercount; i++) {
		userFile << alluser[i]->getname() << " "
			<< alluser[i]->getpass() << " "
			<< alluser[i]->getrole() << endl;
	}
	userFile.close();

	ofstream bookFile("C:\\Users\\HalaH\\OneDrive\\Desktop\\Airport_system1\\Airport_system1\\bookings.txt", ios::out);
	for (int i = 0; i < usercount; i++) {
		customer* cust = dynamic_cast<customer*>(alluser[i]);
		if (cust != nullptr) {
			for (int j = 0; j < cust->get_booking_count(); j++) {
				booking* b = cust->get_booking_by_index(j);
				if (b != nullptr) {
					bookFile << cust->getname() << " "
						<< b->get_fly()->flightnumber << " "
						<< b->getbookingID() << endl;
				}
			}
		}
	}
	userFile.flush();
	bookFile.close();

	cout << "--- All Data Successfully Synced to Database ---" << endl;
}
void booking_system::load_data() {
	flightcount = 0;
	usercount = 0;

	ifstream flightFile("C:\\Users\\HalaH\\OneDrive\\Desktop\\Airport_system1\\Airport_system1\\flights.txt");
	if (flightFile) {
		int type;
		while (flightFile >> type) {
			string fno, src, des; double pr; int seats;
			flightFile >> fno >> src >> des >> pr >> seats;
			if (type == 2) {
				bool v; float t; string s;
				flightFile >> v >> t >> s;
				addflight(new internationalflight(fno, src, des, pr, seats, v, t, s));
			}
			else {
				addflight(new flight(fno, src, des, pr, seats));
			}
		}
		flightFile.close();
	}

	ifstream userFile("C:\\Users\\HalaH\\OneDrive\\Desktop\\Airport_system1\\Airport_system1\\users.txt");
	if (userFile.is_open()) {
		string name, pass, role;
		while (userFile >> name >> pass >> role) {
			user* u = nullptr;

			if (role == "customer") {
				u = new customer();
			}
			else if (role == "admin") {
				u = new administrator();
			}
			else if (role == "agent") {
				u = new agent();
			}

			if (u != nullptr) {
				u->updateprofile(name, pass);
				alluser[usercount] = u;
				usercount++;
				cout << "DEBUG: Loaded User [" << name << "] with role [" << role << "]" << endl;
			}
			else {
				cout << "DEBUG: Failed to identify role [" << role << "] for user [" << name << "]" << endl;
			}
		}
		userFile.close();
	}
	else {
		cout << "ERROR: Could not open users.txt!" << endl;
	}
	ifstream bookFile("C:\\Users\\HalaH\\OneDrive\\Desktop\\Airport_system1\\Airport_system1\\bookings.txt");
	if (bookFile) {
		string custName, flightNo;
		int bID;
		int maxID = 0;
		while (bookFile >> custName >> flightNo >> bID) {
			customer* targetCust = nullptr;
			for (int i = 0; i < usercount; i++) {
				if (alluser[i]->getname() == custName) {
					targetCust = dynamic_cast<customer*>(alluser[i]);
					break;
				}
			}
			flight* targetFlight = nullptr;
			for (int i = 0; i < flightcount; i++) {
				if (allflight[i]->flightnumber == flightNo) {
					targetFlight = allflight[i];
					break;
				}
			}
			if (targetCust && targetFlight) {
				booking* oldB = new booking(bID, targetFlight, targetCust);
				targetCust->addbooking(oldB);
				if (bID > maxID) maxID = bID;
			}
		}
		idcount = maxID + 1;
		bookFile.close();
	}
	cout << "--- System Memory Restored from Files ---" << endl;
}

void booking_system::adduser(user* u)
{
	if (usercount < maxuser) {
		alluser[usercount++] = u;
		cout << "the user has been added successfully" << endl;
	}
	else {
		cout << "the storage of user is fully" << endl;
	}
}

void booking_system::addflight(flight* f)
{
	if (flightcount < maxflight) {
		allflight[flightcount++] = f;
		cout << "the flight number " << f->flightnumber << " has been added successfully " << endl;
	}
	else
		cout << "the schedule of flights is fully" << endl;
}

flight* booking_system::getflight(int index)
{
	if (index >= 0 && index < flightcount) {
		return allflight[index];
	}
	return nullptr;
}

user* booking_system::getuser(int index)
{
	if (index >= 0 && index < usercount) {
		return alluser[index];
	}
	return nullptr;
}

void booking_system::show_allflights()
{
	for (int i = 0;i < flightcount;i++) {
		allflight[i]->display();
	}
}
void booking_system::bookflight(user* u, flight* f, string paydate, string paymethod)
{
	if (!f->checkavailability()) {
		cout << "flight is full!" << endl;
		addlog("booking faild: flight" + f->flightnumber + "is full.");
		return;
	}
	payment* p = new payment(paydate, paymethod);
	p->setamount(f->getprice());
	if (p->processpayment(f)) {
		if (f->bookseat()) {
			booking* newB = new booking(getnextid(), f, (customer*)u);
			((customer*)u)->addbooking(newB);
			addlog("User: " + u->getname() + "successfully booked flight: " + f->flightnumber);
			cout << "Booking successful for user: " << u->getname() << endl;
			p->generatereceipt();

		}
	}
	else
	{
		addlog("Payment declined for user: " + u->getname() + "on flight: " + f->flightnumber);
		cout << "Booking failed: payment declined." << endl;
	}
	delete p;
}
void booking_system::addlog(string message)
{
	if (logcount < 500) {
		systemlogs[logcount++] = message;
	}
}
void booking_system::viewsystemlogs()
{
	if (logcount == 0) {
		cout << "No logs recorded yet." << endl;
		return;
	}
	for (int i = 0;i < logcount;i++) {
		cout << systemlogs[i] << endl;
	}
}
int booking_system::getnextid()
{
	return idcount++;
}

int booking_system::getid()
{
	return idcount;
}

booking_system::~booking_system()
{
	delete[] alluser;
	delete[] allflight;
}
