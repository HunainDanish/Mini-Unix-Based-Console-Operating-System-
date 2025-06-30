#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    cout << "Clock started (running in background)" << endl;
    
    while (true) {
        time_t now = time(nullptr);
        tm* local = localtime(&now);
        
        cout << "\rCurrent time: " << put_time(local, "%H:%M:%S") << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    return 0;
}
