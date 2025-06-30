#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <atomic>


enum class TaskPriority {
    HIGH,       // Interactive tasks (games, UI)
    MEDIUM,     // Normal applications
    LOW         // Background tasks
};

struct Task {
    std::function<void()> function;
    TaskPriority priority;
    int id;
    bool isFinished;
};

class Scheduler {
public:
    Scheduler(int cores);
    ~Scheduler();
    
    int addTask(std::function<void()> task, TaskPriority priority);
    void cancelTask(int taskId);
    void start();
    void stop();
    
private:
    void workerThread();
    void scheduleTasks();
    
    std::vector<std::thread> workers;
    std::queue<Task> highPriorityQueue;
    std::queue<Task> mediumPriorityQueue;
    std::queue<Task> lowPriorityQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> running;
    int nextTaskId;
};

#endif
