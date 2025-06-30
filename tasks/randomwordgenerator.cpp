#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    vector<string> words = {"apple", "banana", "zebra", "coding", "terminal", "system", "os", "power", "bottle", "jungle"};
    srand(time(0));

    cout << "📚 Random Word Generator:\n";
    for (int i = 0; i < 5; ++i) {
        cout << words[rand() % words.size()] << endl;
    }
cout << "Press Enter to exit...";
cin.ignore();
cin.get();

    return 0;
}

