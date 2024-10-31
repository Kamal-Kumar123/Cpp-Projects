#include <iostream>
#include <string> // For using the string class
using namespace std; // Use the standard namespace

// Function to encrypt a message using the Caesar cipher
string encrypt(string message, int shift) {
    string encrypted = ""; // Create an empty string to store the encrypted message

    // Loop through each character in the message
    for (char c : message) {
        // Check if the character is an uppercase letter
        if (c >= 'A' && c <= 'Z') {
            // Shift the character and wrap around using modulo
            c = (c - 'A' + shift) % 26 + 'A'; 
        }
        // Check if the character is a lowercase letter
        else if (c >= 'a' && c <= 'z') {
            // Shift the character and wrap around using modulo
            c = (c - 'a' + shift) % 26 + 'a';
        }
        // Append the shifted character to the encrypted string
        encrypted += c; 
    }

    return encrypted; // Return the encrypted message
}

int main() {
    string message; // Variable to store the message to encrypt
    int shift; // Variable to store the shift value

    // Ask the user for the message
    cout << "Enter the message to encrypt: "; 
    getline(cin, message); // Read the entire line of input
    // Ask the user for the shift value
    cout << "Enter the shift value (1-25): "; 
    cin >> shift; // Read the shift value

    // Ensure shift is within the range of 1 to 25
    if (shift < 1 || shift > 25) {
        cout << "Shift value must be between 1 and 25." << endl; // Error message
        return 1; // Exit the program with an error
    }

    // Call the encrypt function and store the result
    string encryptedMessage = encrypt(message, shift); 
    // Output the encrypted message
    cout << "Encrypted message: " << encryptedMessage << endl; 

    return 0; // Exit the program successfully
}