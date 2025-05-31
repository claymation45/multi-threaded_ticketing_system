#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <sstream>
using namespace std;

mutex print_mutex;

void control_device(const string& action) {
    lock_guard<mutex> lock(print_mutex);
    stringstream ss;
    ss << std::this_thread::get_id();
    cout << "[Thread " << ss.str() << "] Device Control: " << action << endl;
}

void view_status(const string& status) {
    lock_guard<mutex> lock(print_mutex);
    stringstream ss;
    ss << std::this_thread::get_id();
    cout << "[Thread " << ss.str() << "] Device Status: " << status << endl;
}

void show_menu() {
    cout << "===========================\n";
    cout << "   Device Control Menu\n";
    cout << "===========================\n";
    cout << "1. Control Devices\n";
    cout << "2. View Device Status\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    while (true) {
        show_menu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            vector<string> actions = {
                "Turn ON Living Room Light",
                "Turn OFF Bedroom Thermostat",
                "Open Garage Door"
            };
            vector<thread> control_threads;
            for (const auto& act : actions)
                control_threads.emplace_back(control_device, act);
            for (auto& t : control_threads) t.join();
        }
        else if (choice == 2) {
            vector<string> statuses = {
                "Living Room Light: ON",
                "Bedroom Thermostat: 22C",
                "Garage Door: CLOSED",
                "Kitchen Speaker: Playing music"
            };
            vector<thread> status_threads;
            for (const auto& status : statuses)
                status_threads.emplace_back(view_status, status);
            for (auto& t : status_threads) t.join();
        }
        else if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    }
    return 0;
}
