// tasks/calculator.cpp

#include <iostream>
#include <limits>
using namespace std;

int main() {
    int a, b;
    char op;
    char choice;

    cout << "Calculator Started" << endl;

    do {
        cout << "\nEnter expression (e.g., 5 + 3): ";
        cin >> a >> op >> b;

        switch (op) {
            case '+': cout << "Result = " << (a + b) << endl; break;
            case '-': cout << "Result = " << (a - b) << endl; break;
            case '*': cout << "Result = " << (a * b) << endl; break;
            case '/':
                if (b != 0) cout << "Result = " << (a / b) << endl;
                else cout << "Error: Division by zero." << endl;
                break;
            default:
                cout << "Invalid operator." << endl;
        }

        // Ask if user wants to calculate again
        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> choice;

        // Clear buffer just in case
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 'y' || choice == 'Y');

    // Pause before exiting terminal
    cout << "\nPress Enter to close the calculator...";
    cin.get(); // wait for Enter
    return 0;
}

