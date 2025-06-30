#include "resources.h"
#include <iostream>

std::atomic<int> ResourceManager::totalRAM{0};
std::atomic<int> ResourceManager::usedRAM{0};
std::atomic<int> ResourceManager::totalHDD{0};
std::atomic<int> ResourceManager::usedHDD{0};
std::atomic<int> ResourceManager::totalCores{0};
std::atomic<int> ResourceManager::usedCores{0};

void ResourceManager::initialize(int ramMB, int hddGB, int cores) {
    totalRAM = ramMB;
    totalHDD = hddGB * 1024; // Convert GB to MB
    totalCores = cores;
}

bool ResourceManager::allocate(int ram, int hdd, int cores) {
    if (usedRAM + ram > totalRAM || usedHDD + hdd > totalHDD || usedCores + cores > totalCores)
        return false;

    usedRAM += ram;
    usedHDD += hdd;
    usedCores += cores;
    return true;
}

void ResourceManager::release(int ram, int hdd, int cores) {
    usedRAM -= ram;
    usedHDD -= hdd;
    usedCores -= cores;
}

void ResourceManager::showResources() {
    std::cout << "\n📊 System Resource Usage:\n";
    std::cout << "RAM: " << usedRAM << " / " << totalRAM << " MB\n";
    std::cout << "HDD: " << usedHDD << " / " << totalHDD << " MB\n";
    std::cout << "CPU Cores: " << usedCores << " / " << totalCores << "\n\n";
}

