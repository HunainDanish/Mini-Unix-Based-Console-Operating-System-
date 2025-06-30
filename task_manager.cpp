#include "task_manager.h"
#include <sys/wait.h>
#include <iostream>
#include <stdexcept>
#include <signal.h>
#include <thread>

TaskManager& TaskManager::getInstance() {
    static TaskManager instance;
    return instance;
}

int TaskManager::launchTask(const std::string& name, const std::string& command, 
                            int ramNeeded, int hddNeeded, bool isBackground) {
    std::lock_guard<std::mutex> lock(tasksMutex);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("xterm", "xterm", "-e", command.c_str(), (char*) nullptr);
        perror("execlp failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        TaskInfo info{nextPid++, pid, name, ramNeeded, hddNeeded, isBackground, false};
        tasks[pid] = info;

        std::thread([pid]() {
            int status;
            waitpid(pid, &status, 0);
            TaskManager::getInstance().terminateTask(pid); // Clean up on exit
        }).detach();

        return info.pid; // return internal PID
    } else {
        throw std::runtime_error("fork failed");
    }
}

bool TaskManager::terminateTask(int internalPid) {
    std::lock_guard<std::mutex> lock(tasksMutex);

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->second.pid == internalPid) {
            kill(it->first, SIGTERM);
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

bool TaskManager::minimizeTask(int internalPid) {
    std::lock_guard<std::mutex> lock(tasksMutex);
    for (auto& pair : tasks) {
        if (pair.second.pid == internalPid) {
            pair.second.isMinimized = true;
            return true;
        }
    }
    return false;
}

bool TaskManager::restoreTask(int internalPid) {
    std::lock_guard<std::mutex> lock(tasksMutex);
    for (auto& pair : tasks) {
        if (pair.second.pid == internalPid) {
            pair.second.isMinimized = false;
            return true;
        }
    }
    return false;
}

std::vector<TaskInfo> TaskManager::getRunningTasks() const {
    std::lock_guard<std::mutex> lock(tasksMutex);
    std::vector<TaskInfo> result;
    for (const auto& pair : tasks) {
        result.push_back(pair.second);
    }
    return result;
}

