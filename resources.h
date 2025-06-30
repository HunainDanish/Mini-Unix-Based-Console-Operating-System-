#ifndef RESOURCES_H
#define RESOURCES_H

#include <atomic>

class ResourceManager {
public:
    static void initialize(int ramMB, int hddGB, int cores);
    static bool allocate(int ram, int hdd, int cores);
    static void release(int ram, int hdd, int cores);
    static void showResources();

private:
    static std::atomic<int> totalRAM, usedRAM;
    static std::atomic<int> totalHDD, usedHDD;
    static std::atomic<int> totalCores, usedCores;
};

#endif

