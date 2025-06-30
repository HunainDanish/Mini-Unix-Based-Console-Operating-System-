#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    cout << "Downloading file...\n";
    for (int i = 1; i <= 100; ++i) {
        cout << "Progress: " << i << "%\r" << flush;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << "\nDownload complete!\n";
    return 0;
}
