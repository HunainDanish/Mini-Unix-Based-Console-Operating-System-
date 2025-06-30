#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main() {
    int number;
    cout << "Enter a number to check if it's prime: ";
    cin >> number;

    if (isPrime(number))
        cout << number << " is a prime number.\n";
    else
        cout << number << " is not a prime number.\n";

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get(); // Waits for Enter before exiting
    return 0;
}

