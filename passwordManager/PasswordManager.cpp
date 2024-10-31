#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to add a new password
void addPassword() {
    ofstream file("passwords.txt", ios::app); // Open the file to add data at the end
    if (!file) {
        cout << "Unable to open the file!\n";
        return;
    }

    string website, password;
    cout << "Enter the website name: ";
    cin >> website;
    cout << "Enter the password: ";
    cin >> password;

    file << website << " " << password << "\n"; // Save the website and password in the file
    file.close(); // Close the file
    cout << "Password added successfully!\n";
}

// Function to view all passwords
void viewPasswords() {
    ifstream file("passwords.txt"); // Open the file to read data
    if (!file) {
        cout << "Unable to open the file!\n";
        return;
    }

    string website, password;
    cout << "Saved passwords:\n";
    while (file >> website >> password) { // Read each line from the file
        cout << "Website: " << website << ", Password: " << password << "\n"; // Display the data
    }

    file.close(); // Close the file
}

// Main function
int main() {
    int choice;

    while (true) {
        cout << "Password Manager Menu:\n";
        cout << "1. Add Password\n";
        cout << "2. View Passwords\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addPassword(); // Call the function to add a password
        } else if (choice == 2) {
            viewPasswords(); // Call the function to view passwords
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break; // Exit the loop and end the program
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}