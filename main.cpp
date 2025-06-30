#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "resources.h"
#include "task_manager.h"
#include "scheduler.h"

using namespace std;

void showBootScreen() {
    cout << R"(
   ____  _____ ____    _   _   _ ______ _____  
  / __ \| ____/ ___|  | | | | | |  ____|  __ \ 
 | |  | |  _|| (___   | | | | | | |__  | |__) |
 | |  | | |___\___ \  | | | | | |  __| |  _  / 
 | |__| | |_____|_) | |_| | |_| | |____| | \ \ 
  \____/|______|____/  (_) \___/|______|_|  \_\
)" << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "Booting system" << string(i % 3 + 1, '.') << "\r" << flush;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl << "Welcome to STRANGE OS!" << endl;
}

void showMainMenu() {
    cout << R"(
===== SimOS Main Menu =====
 1. Calculator
 2. Notepad
 3. File Manager
 4. Clock
 5. Minesweeper
 6. Music Player
 7. Prime Checker
 8. Task Manager
 9. Timer
 10. Weather App
 11. Download Simulator
 12. Typing Test
 13. Quotes Viewer
 14. Task Logger
 15. Disk Usage Viewer
 16. Random Word Generator
 17. Kernel Mode
 18. Shutdown
===========================
)" << endl;
}

void run(const string& name, const string& cmd, int ram, int hdd, bool background = false) {
    TaskManager::getInstance().launchTask(name, cmd, ram, hdd, background);
}

void showTaskManager() {
    auto tasks = TaskManager::getInstance().getRunningTasks();
    cout << "\nRunning Tasks:\n";
    cout << "PID\tName\t\tRAM\tHDD\tStatus\n";
    for (const auto& task : tasks) {
        cout << task.pid << "\t" << task.name << "\t" 
             << task.ramUsage << "MB\t" << task.hddUsage << "MB\t"
             << (task.isMinimized ? "Minimized" : "Running") << endl;
    }

    cout << "\nOptions:\n1. Terminate Task\n2. Minimize Task\n3. Restore Task\n4. Back\n";
    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
        cout << "Enter PID: ";
        int pid;
        cin >> pid;
        if (choice == 1) TaskManager::getInstance().terminateTask(pid);
        else if (choice == 2) TaskManager::getInstance().minimizeTask(pid);
        else TaskManager::getInstance().restoreTask(pid);
    }
}

void showKernelMode() {
    cout << "\n===== Kernel Mode =====\n";
    cout << "1. View System Resources\n";
    cout << "2. Force Terminate a Task\n";
    cout << "3. Exit Kernel Mode\n";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            ResourceManager::showResources();
            break;
       case 2: {
    auto tasks = TaskManager::getInstance().getRunningTasks();

    cout << "\nRunning Tasks:\n";
    for (const auto& task : tasks) {
        cout << "PID: " << task.pid << " | Name: " << task.name << endl;
    }

    cout << "Enter internal PID to force terminate: ";
    int pid;
    cin >> pid;

    if (!TaskManager::getInstance().terminateTask(pid)) {
        cout << "❌ Failed to terminate task.\n";
    } else {
        cout << "✅ Task terminated.\n";
    }
    break;
}

        case 3:
            cout << "Exiting Kernel Mode...\n";
            break;
        default:
            cout << "Invalid choice.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <RAM_MB> <HDD_GB> <CORES>\n";
        return 1;
    }

    int ram = stoi(argv[1]);
    int hdd = stoi(argv[2]);
    int cores = stoi(argv[3]);

    ResourceManager::initialize(ram, hdd, cores);
    showBootScreen();

    run("Clock", "./tasks/clock", 50, 0, true); // auto-start background clock

    Scheduler scheduler(cores);
    scheduler.start();

    while (true) {
        showMainMenu();
        cout << "Select an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:  run("Calculator", "./tasks/calculator", 100, 0); break;
            case 2:  run("Notepad", "./tasks/notepad", 200, 50); break;
            case 3:  run("File Manager", "./tasks/filemanager", 150, 10); break;
            case 4:  run("Clock", "./tasks/clock", 50, 0, true); break;
            case 5:  run("Minesweeper", "./tasks/minesweeper", 300, 0); break;
            case 6:  run("Music Player", "./tasks/music_player", 150, 100, true); break;
            case 7:  run("Prime Checker", "./tasks/prime_checker", 100, 0); break;
	    case 8:
            	     showTaskManager();
    		     break;

            case 9: run("Timer", "./tasks/timer", 80, 0, true); break;
            case 10: run("Weather App", "./tasks/weather_app", 80, 0); break;
            case 11: run("Download Sim", "./tasks/download_sim", 120, 30, true); break;
            case 12: run("Typing Test", "./tasks/typing_test", 120, 0); break;
            case 13: run("Quotes Viewer", "./tasks/quotes_viewer", 100, 0, true); break;
            case 14: run("Task Logger", "./tasks/task_logger", 80, 20, true); break;
            case 15: run("Disk Usage Viewer", "./tasks/diskusageviewer", 60, 0); break;
            case 16: run("Random Word Generator", "./tasks/randomwordgenerator", 80, 0); break;
            case 17: showKernelMode(); break;
	    case 18:
    		     cout << "Shutting down STRANGE OS..." << endl;
    		     TaskManager::getInstance().shutdownAll(); // ✅ Kill all tasks
    		     scheduler.stop();
		     return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

