#include "flight.h"
#include <iostream>
flight::flight() {}

flight::flight(string fno, string s, string des, double pr, int seat)
{
	flightnumber = fno;
	source = s;
	destination = des;
	price = pr;
	availableseats = seat;

}

bool flight::checkavailability()
{
	if (availableseats > 0)
		return true;
	else
		return false;
}
bool flight::bookseat() {
	if (availableseats > 0) {
		availableseats--;
		return true;
	}
	return false;
}
void flight::releaseseat() {
	availableseats++;
}
double flight::getprice()
{
	return price;
}
void flight::display() {
	cout << flightnumber << endl;
	cout << source << endl;
	cout << destination << endl;
	cout << "--------------------------" << endl;
}

int flight::getavailableseats()
{
	return availableseats;
}
string flight::getflightnum()
{
	return flightnumber;
}
string flight::getdestination()
{
	return destination;
}