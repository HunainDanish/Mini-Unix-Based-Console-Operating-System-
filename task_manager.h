#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include <mutex>
#include <map>
#include <functional>
#include <unistd.h>

struct TaskInfo {
    int pid;               // Internal PID (e.g., 1000, 1001...)
    pid_t realPid;         // Actual OS process ID from fork()
    std::string name;
    int ramUsage;
    int hddUsage;
    bool isBackground;
    bool isMinimized;
};

class TaskManager {
public:
    static TaskManager& getInstance();

    int launchTask(const std::string& name, const std::string& command, 
                   int ramNeeded, int hddNeeded, bool isBackground);
    bool terminateTask(int internalPid);
    bool minimizeTask(int internalPid);
    bool restoreTask(int internalPid);
    std::vector<TaskInfo> getRunningTasks() const;

private:
    TaskManager() = default;
    std::map<pid_t, TaskInfo> tasks; // Key = real OS PID
    mutable std::mutex tasksMutex;
    int nextPid = 1000;
};

#endif

