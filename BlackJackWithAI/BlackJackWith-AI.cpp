#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to get the card value
int getCardValue(char card) {
    if (card >= '2' && card <= '9') {
        return card - '0'; // Numeric value cards (2-9)
    } else if (card == 'T' || card == 'J' || card == 'Q' || card == 'K') {
        return 10; // Face cards and 10
    } else if (card == 'A') {
        return 11; // Ace initially worth 11
    }
    return 0;
}

// Function to get a random card from the deck
char getRandomCard() {
    const char cards[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    return cards[rand() % 13];
}

// Function to calculate the total hand value
int calculateHandValue(const vector<char>& hand) {
    int total = 0;
    int aces = 0;

    // Calculate total value and count aces
    for (char card : hand) {
        int cardValue = getCardValue(card);
        total += cardValue;
        if (card == 'A') {
            aces++;
        }
    }

    // Adjust for aces: if total > 21, count ace as 1 instead of 11
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }

    return total;
}

// Function to display the hand
void displayHand(const vector<char>& hand) {
    for (char card : hand) {
        cout << card << " ";
    }
    cout << "(Total: " << calculateHandValue(hand) << ")" << endl;
}

// Main game logic
int main() {
    srand(time(0));

    vector<char> playerHand;
    vector<char> aiHand;

    // Initial two cards for player and AI
    playerHand.push_back(getRandomCard());
    playerHand.push_back(getRandomCard());
    aiHand.push_back(getRandomCard());
    aiHand.push_back(getRandomCard());

    cout << "Welcome to Blackjack!" << endl;

    // Player's turn
    bool playerStands = false;
    while (!playerStands && calculateHandValue(playerHand) <= 21) {
        cout << "\nYour hand: ";
        displayHand(playerHand);

        cout << "AI's visible card: " << aiHand[0] << endl;

        // Player action: hit or stand
        char choice;
        cout << "Do you want to (h)it or (s)tand? ";
        cin >> choice;

        if (choice == 'h' || choice == 'H') {
            playerHand.push_back(getRandomCard());
        } else if (choice == 's' || choice == 'S') {
            playerStands = true;
        }
    }

    int playerTotal = calculateHandValue(playerHand);
    cout << "\nYour final hand: ";
    displayHand(playerHand);

    if (playerTotal > 21) {
        cout << "You busted! You lose." << endl;
        return 0;
    }

    // AI's turn
    cout << "\nAI's turn..." << endl;
    while (calculateHandValue(aiHand) < 17) {
        aiHand.push_back(getRandomCard());
    }

    int aiTotal = calculateHandValue(aiHand);
    cout << "AI's final hand: ";
    displayHand(aiHand);

    // Determine the winner
    if (aiTotal > 21 || playerTotal > aiTotal) {
        cout << "You win!" << endl;
    } else if (aiTotal == playerTotal) {
        cout << "It's a tie!" << endl;
    } else {
        cout << "AI wins!" << endl;
    }

    return 0;
}