#include "user.h"
#include "customer.h"
#include "administrator.h"
#include "agent.h"
#include "flight.h"
#include "booking_system.h"
#include "internationalflight.h"
#include "payment.h"
#include "booking.h"
#include <iostream>
#include <fstream>
using namespace std;
string admin_code = "ADMIN_SECURE_ACCESS_2024_SYS";
string agent_code = "AGENT_SECURE_ACCESS_2024_SYS";
void cancel(customer*);
int main() {
    int no_users, no_flights;
    cout << "enter the number of users" << endl;
    cin >> no_users;
    cout << "enter the number of flights" << endl;
    cin >> no_flights;
    booking_system* sys = new booking_system(no_users, no_flights);
    sys->load_data();
    while (true) {
        string role;
        cout << "Welcome to Flight System!" << endl;
        cout << "Please enter your role (admin / customer / agent): ";
        cin >> role;

        if (role == "admin") {
            administrator* admin = nullptr;
            cout << "--- Admin Login ---" << endl;
            string secret_code;
            cout << "enter the secret code please" << endl;
            cin >> secret_code;
            if (secret_code == admin_code) {
                string admin_name, admin_password;
                bool isValid = false;
                while (!isValid) {
                    cout << "Please enter your name and password: ";
                    cin >> admin_name >> admin_password;
                    customer c1;
                    if (c1.isvalidpassword(admin_password)) {
                        for (int i = 0; i < sys->usercount; i++) {
                            if (sys->getuser(i)->getname() == admin_name && sys->getuser(i)->getpass() == admin_password) {
                                admin = dynamic_cast<administrator*>(sys->getuser(i));
                                break;
                            }
                        }
                        if (admin != nullptr) {
                            isValid = true;
                        }
                        else {
                            cout << "Admin credentials not found in system! Try again.\n";
                        }
                    }
                    else {
                        cout << "Invalid password! Must be at least 8 characters. Try again.\n";
                    }
                }
                cout << "Do you want to update your profile ? (y/n)" << endl;
                char update;
                cin >> update;
                if (update == 'y' || update == 'Y') {
                    string new_name, new_pass;
                    cout << "Please enter your new name and password" << endl;
                    cin >> new_name >> new_pass;
                    admin->updateprofile(new_name, new_pass);
                }
                int users;
                cout << "How many users to add? ";
                cin >> users;
                for (int i = 0; i < users; i++) {
                    string uname, upass;
                    bool isValid = false;
                    while (!isValid) {
                        cout << "Please enter the name and password for user " << i + 1 << " :";
                        cin >> uname >> upass;
                        if (!uname.empty() && upass.length() >= 8) {
                            isValid = true;
                        }
                        else {
                            cout << "Invalid password! Must be at least 8 characters. Try again.\n";
                        }
                    }

                    customer* newCust = new customer();
                    newCust->updateprofile(uname, upass);
                    admin->addnewuser(*sys, newCust);
                }
                int no_of_daily_flights;
                cout << "Enter the no.of available daily flights: ";
                cin >> no_of_daily_flights;
                cout << endl;
                if (no_of_daily_flights <= no_flights) {
                    for (int i = 0;i < no_of_daily_flights;i++) {
                        int type;
                        cout << "Flight type? (1: National, 2: International): ";
                        cin >> type;
                        string fly_num, src, des;
                        double ticket_price;
                        int aval_seats;
                        cout << "Flight " << i + 1 << " Details (Number, Source, Des, Price, Seats): " << endl;
                        cin >> fly_num >> src >> des >> ticket_price >> aval_seats;
                        flight* fptr = nullptr;
                        if (type == 2) {
                            bool visa;
                            float tax;
                            string service;
                            cout << "Visa required? (1: Yes, 0: No): ";
                            cin >> visa;
                            cout << "International Tax: ";
                            cin >> tax;
                            cout << "Additional Services: ";
                            cin >> service;
                            fptr = new internationalflight(fly_num, src, des, ticket_price, aval_seats, visa, tax, service);
                        }
                        else {
                            fptr = new flight(fly_num, src, des, ticket_price, aval_seats);
                        }
                        if (fptr != nullptr) {
                            admin->addnewflight(*sys, fptr);
                        }
                    }
                }
                sys->save_data();
                cout << "System updated. Admin logs:" << endl;
                admin->monitorsystem(*sys);
            }
            else
                cout << "you are not admin!" << endl;

        }

        else if (role == "customer")
        {
            cout << "1. Register (New User)\n2. Login (Existing User)\nChoice: ";
            int choice;
            cin >> choice;
            customer* currentCust = nullptr;
            if (choice == 1) {
                string cust_name, cust_pass;
                bool isValid = false;
                while (!isValid) {
                    cout << "Please enter your name and password: ";
                    cin >> cust_name >> cust_pass;
                    if (currentCust->isvalidpassword(cust_pass)) {
                        isValid = true;
                    }
                    else {
                        cout << "Invalid password! Must be at least 8 characters. Try again.\n";
                    }
                }
                currentCust->updateprofile(cust_name, cust_pass);
                sys->adduser(currentCust);
                cout << "Register completed successfully! Welcome " << currentCust->getname() << endl;
            }
            else if (choice == 2) {
                string cust_name, cust_pass;
                bool isValid = false;
                while (!isValid) {
                    cout << "Please enter your name and password: ";
                    cin >> cust_name >> cust_pass;
                    if (currentCust->isvalidpassword(cust_pass)) {
                        isValid = true;
                    }
                    else {
                        cout << "Invalid password! Must be at least 8 characters. Try again.\n";
                    }
                }
                for (int i = 0; i < sys->usercount; i++) {
                    if (sys->getuser(i)->getname() == cust_name && sys->getuser(i)->getpass() == cust_pass) {
                        currentCust = dynamic_cast<customer*>(sys->getuser(i));
                        break;
                    }
                }
                if (currentCust == nullptr) {
                    cout << "[!] Login Failed: User not found or wrong password." << endl;
                    continue;
                }
                cout << "Login successful! Welcome " << currentCust->getname() << endl;
            }

            if (currentCust != nullptr) {
                cout << "Do you want to update your profile? (y/n): ";
                char up;
                cin >> up;
                if (up == 'y' || up == 'Y') {
                    string n, p;
                    cout << "Enter new name and password:" << endl;
                    cin >> n >> p;
                    currentCust->updateprofile(n, p);
                }
                cout << " Available Flights:" << endl;
                sys->show_allflights();
                cout << "\n--- Customer Searching Flights ---" << endl;
                string dest;
                cout << "Enter your desired destination: ";
                cin >> dest;
                currentCust->searchflights(dest, sys);
                cout << "\nDo you want to book a flight? (y/n): ";
                char choice_1;
                cin >> choice_1;
                if (choice_1 == 'y' || choice_1 == 'Y') {
                    if (sys->flightcount > 0) {
                        string p_date, p_method, targetFlightNo;
                        cout << "Enter the Flight Number you want to book: ";
                        cin >> targetFlightNo;
                        flight* selectedFlight = nullptr;
                        for (int i = 0; i < sys->flightcount; i++) {

                            if (sys->getflight(i)->getflightnum() == targetFlightNo) {
                                selectedFlight = sys->getflight(i);
                                break;
                            }
                        }
                        if (selectedFlight != nullptr) {
                            cout << "Enter your desired flight date & payment method: ";
                            cin >> p_date;
                            cin.ignore();
                            getline(cin, p_method);
                            sys->bookflight(currentCust, selectedFlight, p_date, p_method);
                            sys->save_data();
                            currentCust->view_my_bookings();
                        }

                        else {
                            cout << "Error: Flight number not found!" << endl;
                        }
                    }

                    else {
                        cout << "Sorry, there are no flights available to book." << endl;
                    }
                }
                cout << "\n--- Customer View & Cancel Booking ---" << endl;
                currentCust->view_my_bookings();
                cout << "Do you want to cancel any booking ? (y/n)" << endl;
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    cancel(currentCust);
                }
                cout << "\n--- Updated Bookings List ---" << endl;
                currentCust->view_my_bookings();
                sys->save_data();
            }
        }
        else if (role == "agent")
        {
            string secret_code;
            cout << "enter the secret code please" << endl;
            cin >> secret_code;
            if (secret_code == agent_code) {
                agent* agent1 = nullptr;
                string agent_name, agent_pass;
                bool isValid = false;
                while (!isValid) {
                    cout << "Please enter your name and password: ";
                    cin >> agent_name >> agent_pass;
                    customer c1;
                    if (c1.isvalidpassword(agent_pass)) {
                        for (int i = 0; i < sys->usercount; i++) {
                            if (sys->getuser(i)->getname() == agent_name && sys->getuser(i)->getpass() == agent_pass) {
                                agent1 = dynamic_cast<agent*>(sys->getuser(i));
                                break;
                            }
                        }
                        if (agent1 != nullptr) {
                            isValid = true;
                        }
                        else {
                            cout << "Agent credentials not found in system! Try again.\n";
                        }
                    }
                    else {
                        cout << "Invalid password! Must be at least 8 characters. Try again.\n";
                    }
                }
                agent1->updateprofile(agent_name, agent_pass);
                cout << "Agent " << agent1->getname() << " is ready to process bookings." << endl;
                cout << "--- System Check: I have " << sys->usercount << " users in my memory right now ---" << endl;
                for (int i = 0; i < sys->usercount; i++) {
                    cout << "User " << i + 1 << ": " << sys->getuser(i)->getname() << endl;
                }
                string targetCustomerName;
                cout << "Enter Customer Name to book for: ";
                cin >> targetCustomerName;

                customer* targetCust = nullptr;
                for (int i = 0; i < sys->usercount; i++) {
                    cout << "Checking system user: " << sys->getuser(i)->getname() << endl;
                    if (sys->getuser(i)->getname() == targetCustomerName) {
                        targetCust = (customer*)sys->getuser(i); // casting from user to customer
                        break;
                    }
                }
                string targetFlightNo;
                cout << "Enter Flight Number: ";
                cin >> targetFlightNo;

                flight* targetFptr = nullptr;
                for (int i = 0; i < sys->flightcount; i++) {
                    if (sys->getflight(i)->getflightnum() == targetFlightNo) {
                        targetFptr = sys->getflight(i);
                        break;
                    }
                }
                if (targetCust != nullptr && targetFptr != nullptr) {
                    string p_date, p_method;
                    cout << "Enter date and method: ";
                    cin >> p_date;
                    cin.ignore();
                    getline(cin, p_method);
                    payment* p = new payment(p_date, p_method);
                    agent1->processbooking(targetCust, targetFptr, sys, p);

                    cout << "\nAgent successfully processed the booking!" << endl;
                    agent1->generatereports();
                }
                else {
                    cout << "Error: Customer or Flight not found in system!" << endl;
                }
                sys->save_data();
            }
            else
            {
                cout << "you are not agent!" << endl;
            }
        }


    }
    delete sys;
    return 0;
}
void cancel(customer* user) {
    cout << "How many flights do you want to cancel ?" << endl;
    int n;
    bool flag = true;
    while (flag) {
        cin >> n;
        if (n <= user->getbookingcount()) {
            for (int i = 0;i < n;i++) {
                int idFromUser;
                cout << "\nEnter the Booking ID you want to cancel: ";
                cin >> idFromUser;
                user->CancelBooking(idFromUser);
            }
            flag = false;
        }
        else {
            cout << "ERROR[!] you want to cancel no.of flights greater than your booked flights!" << endl;
            cout << "Please enter a correct number of flights! " << endl;;
        }

    }
}