#include "agent.h"
#include <iostream>
agent::agent()
{
	role = "agent";
	totalsales = 0.0;
	commissionrate = 0.1;
}

void agent::processbooking(customer* c, flight* f, booking_system* system, payment* p) {
	cust = c;
	flightdetails = f;
	if (!(flightdetails->checkavailability())) {
		cout << "Sorry no places available" << endl;

	}
	else {
		p->setamount(f->getprice());
		if (p->processpayment(f)) {
			flightdetails->bookseat();
			booking* b = new booking(booking_system::getnextid(), f, c);
			cust->addbooking(b);
			this->totalsales += f->getprice();
			cout << "\nGenerating your receipt..." << endl;
			p->generatereceipt();
			cout << "Agent processed the booking and saved to the system.";
		}
		else {
			cout << "Payment failed! Booking cancelled." << endl;
		}
	}
}
double agent::calculatecommision() {
	return this->totalsales * this->commissionrate;
}

void agent::generatereports() {
	cout << "Agent name: " << this->getname() << endl;
	cout << "Total Sales Achieved: " << this->totalsales << endl;
	cout << "Total Commission Earned: " << this->calculatecommision() << endl;
	cout << "Commission Rate: " << (this->commissionrate * 100) << endl;
}
string agent::getrole() {

	return role;
}
