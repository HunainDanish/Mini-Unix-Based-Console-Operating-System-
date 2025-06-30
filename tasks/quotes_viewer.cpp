#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    string quotes[] = {
        "Believe you can and you're halfway there.",
        "Do not wait to strike till the iron is hot; but make it hot by striking.",
        "Great minds discuss ideas; average minds discuss events; small minds discuss people.",
        "The best way to predict the future is to invent it."
    };
    for (const auto& quote : quotes) {
        cout << quote << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
    return 0;
}
