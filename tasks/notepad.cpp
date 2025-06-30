#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <atomic>
#include <csignal>

using namespace std;

vector<string> buffer;
mutex mtx;
atomic<bool> running(true);
atomic<bool> modified(false); // Tracks if new content is added

void handleExit(int signal) {
    lock_guard<mutex> lock(mtx);
    if (modified) {
        ofstream file("notepad_save.txt");
        for (const auto& line : buffer)
            file << line << endl;
        file.flush();
        cout << "\n\n[Notepad saved before forced close]\n";
    } else {
        cout << "\n\n[No changes to save]\n";
    }
    exit(0);
}

void autosave() {
    while (running) {
        this_thread::sleep_for(chrono::seconds(2));
        lock_guard<mutex> lock(mtx);
        if (modified) {
            ofstream file("notepad_save.txt");
            for (const auto& line : buffer)
                file << line << endl;
            file.flush();
            cout << "[Autosave complete]\n";
            modified = false;
        }
    }
}

int main() {
    signal(SIGINT, handleExit);
    signal(SIGTERM, handleExit);
    signal(SIGHUP, handleExit);

    // Load previous content
    ifstream infile("notepad_save.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            buffer.push_back(line);
        }
        infile.close();

        cout << "\n[Previous Notes Loaded:]\n";
        for (const auto& l : buffer)
            cout << l << endl;
        cout << "\n--- Start Typing Below ---\n";
    }

    cout << "Notepad Started. Type your text below." << endl;
    cout << "(Type ':exit' on a new line to finish)\n" << endl;

    thread saver(autosave);

    string line;
    while (true) {
        getline(cin, line);
        if (line == ":exit") break;

        {
            lock_guard<mutex> lock(mtx);
            buffer.push_back(line);
            modified = true;

            ofstream file("notepad_save.txt");
            for (const auto& l : buffer)
                file << l << endl;
            file.flush();
        }
    }

    running = false;
    saver.join();

    // Final save before exit
    {
        lock_guard<mutex> lock(mtx);
        if (modified) {
            ofstream file("notepad_save.txt");
            for (const auto& l : buffer)
                file << l << endl;
            file.flush();
            cout << "\nFinal save complete.\n";
        } else {
            cout << "\nNo changes to save.\n";
        }
    }

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}

