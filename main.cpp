
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits>
using namespace std;

// Passenger information
struct Passenger {
    int ticketID;
    string name;
    string flightNumber;
    int age;
    int seatNumber;
    bool checkedIn;
};

// Airport Check-In Management System
class AirportCheckIn {
private:
    queue<int> checkInQueue;
    unordered_map<int, Passenger> passengers;
    vector<int> checkedInPassengers;
    unordered_map<string, set<int>> occupiedSeats;

    const int MAX_SEATS = 180;

public:

    // 1. Register a passenger
    void registerPassenger() {
        Passenger p;

        cout << "\nEnter Ticket ID: ";
        cin >> p.ticketID;

        if (passengers.count(p.ticketID)) {
            cout << "Ticket ID already exists!\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Passenger Name: ";
        getline(cin, p.name);

        cout << "Enter Age: ";
        cin >> p.age;

        cout << "Enter Flight Number: ";
        cin >> p.flightNumber;

        p.checkedIn = false;
        p.seatNumber = -1;

        passengers[p.ticketID] = p;
        checkInQueue.push(p.ticketID);

        cout << "\nPassenger registered successfully!\n";
        cout << "Added to check-in queue.\n";
        cout << "Queue Position: "
             << checkInQueue.size() << "\n";
    }

    // 2. Process next passenger
    void checkInPassenger() {
        if (checkInQueue.empty()) {
            cout << "\nNo passengers waiting!\n";
            return;
        }

        int id = checkInQueue.front();
        checkInQueue.pop();

        Passenger &p = passengers[id];

        int seat = -1;

        // Allocate the first available seat
        for (int i = 1; i <= MAX_SEATS; i++) {
            if (!occupiedSeats[p.flightNumber].count(i)) {
                seat = i;
                break;
            }
        }

        if (seat == -1) {
            cout << "\nFlight is full!\n";
            checkInQueue.push(id);
            return;
        }

        p.seatNumber = seat;
        p.checkedIn = true;

        occupiedSeats[p.flightNumber].insert(seat);
        checkedInPassengers.push_back(id);

        cout << "\nCheck-in successful!\n";
        printBoardingPass(p);
    }

    // 3. Print boarding pass
    void printBoardingPass(const Passenger &p) {
        cout << "\n============================\n";
        cout << "        BOARDING PASS       \n";
        cout << "============================\n";
        cout << "Ticket ID : " << p.ticketID << "\n";
        cout << "Name      : " << p.name << "\n";
        cout << "Age       : " << p.age << "\n";
        cout << "Flight    : " << p.flightNumber << "\n";
        cout << "Seat      : " << p.seatNumber << "\n";
        cout << "Status    : CHECKED IN\n";
        cout << "============================\n";
    }

    // 4. Search passenger using Hash Map
    void searchPassenger() {
        int id;
        cout << "\nEnter Ticket ID: ";
        cin >> id;

        auto it = passengers.find(id);

        if (it == passengers.end()) {
            cout << "Passenger not found!\n";
            return;
        }

        Passenger &p = it->second;

        cout << "\nPassenger Details\n";
        cout << "------------------------\n";
        cout << "Name   : " << p.name << "\n";
        cout << "Age    : " << p.age << "\n";
        cout << "Flight : " << p.flightNumber << "\n";

        if (p.checkedIn) {
            cout << "Status : Checked In\n";
            cout << "Seat   : " << p.seatNumber << "\n";
        } else {
            cout << "Status : Waiting\n";
        }
    }

    // 5. Display waiting queue
    void displayQueue() {
        if (checkInQueue.empty()) {
            cout << "\nCheck-in queue is empty!\n";
            return;
        }

        queue<int> temp = checkInQueue;
        int position = 1;

        cout << "\nPassengers Waiting\n";
        cout << "------------------------\n";

        while (!temp.empty()) {
            int id = temp.front();
            temp.pop();

            Passenger &p = passengers[id];

            cout << position++ << ". "
                 << p.name
                 << " | Ticket: " << p.ticketID
                 << " | Flight: " << p.flightNumber
                 << "\n";
        }
    }

    // 6. Display checked-in passengers
    void displayCheckedIn() {
        if (checkedInPassengers.empty()) {
            cout << "\nNo checked-in passengers!\n";
            return;
        }

        cout << "\nChecked-In Passengers\n";
        cout << "------------------------\n";

        for (int id : checkedInPassengers) {
            Passenger &p = passengers[id];

            cout << "Name: " << p.name
                 << " | Flight: " << p.flightNumber
                 << " | Seat: " << p.seatNumber
                 << "\n";
        }
    }

    // 7. Display airport statistics
    void displayStatistics() {
        cout << "\n===== AIRPORT STATISTICS =====\n";
        cout << "Total Registered : "
             << passengers.size() << "\n";
        cout << "Waiting          : "
             << checkInQueue.size() << "\n";
        cout << "Checked In       : "
             << checkedInPassengers.size() << "\n";
    }
};

int main() {
    AirportCheckIn airport;
    int choice;

    do {
        cout << "\n================================\n";
        cout << "   AIRPORT CHECK-IN SYSTEM\n";
        cout << "================================\n";
        cout << "1. Register Passenger\n";
        cout << "2. Check In Next Passenger\n";
        cout << "3. Search Passenger\n";
        cout << "4. Display Waiting Queue\n";
        cout << "5. Display Checked-In Passengers\n";
        cout << "6. Airport Statistics\n";
        cout << "7. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            break;
        }

        switch (choice) {
            case 1:
                airport.registerPassenger();
                break;

            case 2:
                airport.checkInPassenger();
                break;

            case 3:
                airport.searchPassenger();
                break;

            case 4:
                airport.displayQueue();
                break;

            case 5:
                airport.displayCheckedIn();
                break;

            case 6:
                airport.displayStatistics();
                break;

            case 7:
                cout << "\nExiting Airport System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
