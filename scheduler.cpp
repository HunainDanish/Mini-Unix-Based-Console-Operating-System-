#include "scheduler.h"
#include <iostream>

Scheduler::Scheduler(int cores) : running(false), nextTaskId(1) {
    workers.reserve(cores);
}

Scheduler::~Scheduler() {
    stop();
}

int Scheduler::addTask(std::function<void()> task, TaskPriority priority) {
    std::lock_guard<std::mutex> lock(queueMutex);
    Task newTask{task, priority, nextTaskId++, false};
    
    switch(priority) {
        case TaskPriority::HIGH:
            highPriorityQueue.push(newTask);
            break;
        case TaskPriority::MEDIUM:
            mediumPriorityQueue.push(newTask);
            break;
        case TaskPriority::LOW:
            lowPriorityQueue.push(newTask);
            break;
    }
    
    cv.notify_one();
    return newTask.id;
}

void Scheduler::cancelTask(int taskId) {
    // Implementation would search queues and remove task
    // Simplified for this example
}

void Scheduler::start() {
    running = true;
    for (size_t i = 0; i < workers.capacity(); ++i) {
        workers.emplace_back(&Scheduler::workerThread, this);
    }
}

void Scheduler::stop() {
    running = false;
    cv.notify_all();
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void Scheduler::workerThread() {
    while (running) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
           cv.wait(lock, [this]() -> bool {
    return !highPriorityQueue.empty() || 
           !mediumPriorityQueue.empty() || 
           !lowPriorityQueue.empty() || !running;
});

            if (!running) break;
            
            // Priority scheduling
            if (!highPriorityQueue.empty()) {
                task = highPriorityQueue.front();
                highPriorityQueue.pop();
            } else if (!mediumPriorityQueue.empty()) {
                task = mediumPriorityQueue.front();
                mediumPriorityQueue.pop();
            } else {
                task = lowPriorityQueue.front();
                lowPriorityQueue.pop();
            }
        }
        
        // Execute task
        task.function();
    }
}
