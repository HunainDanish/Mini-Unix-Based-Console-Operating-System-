#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
#include <csignal>
#include <sys/wait.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;

const string musicDir = "./tasks/songs/";

// Function to get single key press without waiting for Enter
char getCharNonBlocking() {
    struct termios oldt, newt;
    char ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);          // Save old terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // Disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}

vector<string> getPlaylist() {
    vector<string> playlist;
    DIR* dir = opendir(musicDir.c_str());
    if (!dir) {
        perror("opendir failed");
        exit(1);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (name.size() > 4 && (
            name.substr(name.size() - 4) == ".mp3" ||
            name.substr(name.size() - 4) == ".wav" ||
            name.substr(name.size() - 4) == ".ogg")) {
            playlist.push_back(musicDir + name);
        }
    }
    closedir(dir);
    return playlist;
}

int main() {
    vector<string> playlist = getPlaylist();
    if (playlist.empty()) {
        cout << "No audio files found in: " << musicDir << endl;
        return 1;
    }

    cout << "🎵 Interactive Music Player Started\n";

    for (size_t i = 0; i < playlist.size(); ++i) {
        string song = playlist[i];
        cout << "\n▶️ Now Playing: " << song << endl;
        cout << "Press 'n' to skip to the next song...\n";

        pid_t pid = fork();
        if (pid == 0) {
    // Child: silence output
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);

    // Child: play song
    execlp("ffplay", "ffplay", "-nodisp", "-autoexit", song.c_str(), nullptr);
    perror("execlp failed");
    exit(1);
}


        // Parent: check for 'n' to skip
        while (true) {
            usleep(200000); // Sleep for 200ms
            char c = getCharNonBlocking();
            if (c == 'n' || c == 'N') {
                kill(pid, SIGKILL);
                waitpid(pid, nullptr, 0);
                cout << "⏭️ Skipped!\n";
                break;
            }

            // Check if song finished
            int status;
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == pid)
                break;
        }
    }

    cout << "🎶 Playlist finished.\n";
    return 0;
}

