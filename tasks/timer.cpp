#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    int seconds;
    cout << "Set a timer (seconds): ";
    cin >> seconds;
    while (seconds > 0) {
        cout << "Time left: " << seconds << "s\r" << flush;
        this_thread::sleep_for(chrono::seconds(1));
        --seconds;
    }
    cout << "\nTime's up!\n";
cout << "Press Enter to exit...";
cin.ignore();
cin.get();

    return 0;
}
