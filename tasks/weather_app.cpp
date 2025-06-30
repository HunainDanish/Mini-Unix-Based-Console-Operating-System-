#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    string weather[] = {"Sunny", "Rainy", "Cloudy", "Windy", "Stormy"};
    int temp = rand() % 40;
    string w = weather[rand() % 5];
    cout << "Today's Weather: " << w << ", " << temp << "°C\n";
cout << "Press Enter to exit...";
cin.ignore();
cin.get();

    return 0;
}
