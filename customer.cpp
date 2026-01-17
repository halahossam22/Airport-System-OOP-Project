#include "customer.h"
#include <iostream>
void customer::searchflights(string des, booking_system* bs) {
	bool found = false;
	cout << "Search Results for Destination " << des << endl;
	for (int i = 0; i < bs->flightcount; i++) {
		flight* current_flight = bs->getflight(i);
		if (current_flight != nullptr) {
			if (current_flight->getdestination() == des) {
				current_flight->display();
				found = true;
			}
		}

	}
	if (!found) {
		cout << "No Flights found for this destination :(" << endl;
	}
}
customer::customer() {
	role = "customer";
	booking_count = 0;
	for (int i = 0; i < 20; i++) {
		mybookings[i] = nullptr;
	}
}

int customer::getbookingcount()
{
	return booking_count;
}

void customer::addbooking(booking* b) {
	if (booking_count >= 20) {
		cout << "Sorry, Maximum flight reservations count reached!";
	}
	else {
		mybookings[booking_count++] = b;
	}
}

int customer::get_booking_count()
{
	return booking_count;
}

booking* customer::get_booking_by_index(int index)
{
	if (index >= 0 && index < booking_count) {
		return mybookings[index];
	}
	return nullptr;
}

void customer::view_my_bookings() {
	cout << "DEBUG: Current booking_count is: " << booking_count << endl;
	if (booking_count == 0) {
		cout << "You have no bookings yet!" << endl;
		return;
	}
	cout << "----Your Booking List----" << endl;
	for (int i = 0; i < booking_count; i++) {
		booking* b = mybookings[i];
		if (b != nullptr) {
			cout << "Booking " << (i + 1) << ": " << endl;
			b->displaybookingdetails();
			cout << "------------------------" << endl;
		}
	}
}

void customer::CancelBooking(int ID) {
	if (booking_count <= 0) {
		cout << "Error: No bookings available to cancel." << endl;
		return;
	}
	bool found = false;
	for (int i = 0; i < booking_count; i++) {
		if (mybookings[i] != nullptr && mybookings[i]->getbookingID() == ID) {
			mybookings[i]->cancelbooking();
			delete mybookings[i];
			for (int j = i; j < booking_count - 1; j++) {
				mybookings[j] = mybookings[j + 1];
			}
			mybookings[booking_count - 1] = nullptr;
			booking_count--;
			found = true;
			cout << "Booking " << ID << " has been removed from your list." << endl;
			break;
		}
	}
	if (!found) {
		cout << "Error: Booking ID " << ID << " not found in your list." << endl;
	}
}
string customer::getrole() {

	return role;
}




