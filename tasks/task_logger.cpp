#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    ofstream log("task_log.txt", ios::app);
    if (!log) {
        cerr << "Failed to open log file.\n";
        return 1;
    }
    for (int i = 1; i <= 5; ++i) {
        log << "Task running at interval " << i << "\n";
        log.flush();
        this_thread::sleep_for(chrono::seconds(5));
    }
    log.close();
    cout << "Task logging complete.\n";
cout << "Press Enter to exit...";
    cin.get();
    return 0;
}
