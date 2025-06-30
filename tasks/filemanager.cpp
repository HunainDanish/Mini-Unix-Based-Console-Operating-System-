#include <iostream>
#include <fstream>
#include <cstdio>       // for remove(), rename()
#include <unistd.h>     // for access()
#include <sys/stat.h>   // for stat()
using namespace std;

void createFile() {
    string filename;
    cout << "Enter file name to create: ";
    cin >> filename;
    ofstream file(filename);
    if (file) cout << "File created successfully.\n";
    else cout << "Failed to create file.\n";
}

void deleteFile() {
    string filename;
    cout << "Enter file name to delete: ";
    cin >> filename;
    if (remove(filename.c_str()) == 0)
        cout << "File deleted successfully.\n";
    else
        perror("Error deleting file");
}

void renameFile() {
    string oldName, newName;
    cout << "Enter current file name: ";
    cin >> oldName;
    cout << "Enter new file name: ";
    cin >> newName;
    if (rename(oldName.c_str(), newName.c_str()) == 0)
        cout << "File renamed successfully.\n";
    else
        perror("Error renaming file");
}

void fileInfo() {
    string filename;
    cout << "Enter file name to view info: ";
    cin >> filename;

    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) == 0) {
        cout << "File Size: " << fileStat.st_size << " bytes\n";
        cout << "Permissions: ";
        cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-") << endl;
    } else {
        perror("Error retrieving file info");
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n===== File Manager =====\n";
        cout << "1. Create File\n";
        cout << "2. Delete File\n";
        cout << "3. Rename File\n";
        cout << "4. File Info\n";
        cout << "5. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: renameFile(); break;
            case 4: fileInfo(); break;
            case 5:
                cout << "Exiting File Manager.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

