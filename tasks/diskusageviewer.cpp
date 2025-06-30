#include <iostream>
#include <sys/statvfs.h>
using namespace std;

int main() {
    struct statvfs stat;
    if (statvfs(".", &stat) != 0) {
        perror("statvfs failed");
        return 1;
    }

    unsigned long total = stat.f_blocks * stat.f_frsize;
    unsigned long free = stat.f_bfree * stat.f_frsize;
    unsigned long used = total - free;

    cout << "📦 Disk Usage Info:\n";
    cout << "Total: " << total / (1024 * 1024) << " MB\n";
    cout << "Used : " << used / (1024 * 1024) << " MB\n";
    cout << "Free : " << free / (1024 * 1024) << " MB\n";
cout << "Press Enter to exit...";
cin.ignore();
cin.get();

    return 0;
}

