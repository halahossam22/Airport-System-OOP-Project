#include "customer.h"
#include "booking.h"
#include <iostream>
booking::booking(int id, flight* f, customer* p)
{
	bookingID = id;
	passenger = p;
	fly = f;
	status = "confirmed";
}
void booking::displaybookingdetails() {
	cout << passenger->getname() << endl;
	cout << bookingID << endl;
	fly->display();
	cout << status << endl;

}

void booking::cancelbooking()
{
	status = "cancelled";
	fly->releaseseat();
}

int booking::getbookingID()
{
	return bookingID;
}
flight *booking::get_fly() {
	return fly;
}
