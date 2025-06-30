#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace chrono;

// Helper function to trim leading/trailing whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

int main() {
    // Sentences to type
    vector<string> phrases = {
        "The quick brown fox jumps over the lazy dog",
        "C++ is a powerful programming language",
        "Typing practice makes you faster",
        "Consistency is the key to improvement",
        "Debugging is like being a detective"
    };

    // Pick a random phrase
    srand(static_cast<unsigned int>(time(0)));
    string test = phrases[rand() % phrases.size()];

    // Show prompt
    cout << "Type the following sentence exactly:\n" << test << "\n\nYour input:\n";

    // Clean any prior input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Atomic flag and timer thread
    atomic<bool> done(false);
    thread timerThread([&done]() {
        int seconds = 0;
        while (!done) {
            cout << "\r⏱️ Time elapsed: " << seconds++ << "s   " << flush;
            this_thread::sleep_for(seconds == 1 ? chrono::milliseconds(900) : chrono::seconds(1));
        }
    });

    // Record start time and get user input
    auto start = high_resolution_clock::now();
    string input;
    getline(cin, input);
    auto end = high_resolution_clock::now();
    done = true;

    // Stop timer thread
    if (timerThread.joinable()) timerThread.join();

    // Calculate elapsed time
    duration<double> diff = end - start;
    cout << "\n\n";

    // Result
    if (trim(input) == test)
        cout << "✅ Perfect typing! Time taken: " << diff.count() << " seconds.\n";
    else
        cout << "❌ Mismatch. Try again.\n";

    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}

