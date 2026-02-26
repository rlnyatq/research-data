#include <iostream>
#include <string>
using namespace std;

// Function to calculate binomial coefficient C(n, k) = n! / (k! * (n-k)!)
// This represents the number of ways to choose k items from n items
long long binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;
    
    // Use the property C(n,k) = C(n,n-k) to minimize calculations
    if (k > n - k) k = n - k;
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// Function to check if a word is valid (strictly ascending letters)
bool isValid(const string& word) {
    for (int i = 1; i < word.length(); i++) {
        // Each letter must be strictly greater than the previous one
        if (word[i] <= word[i-1]) {
            return false;
        }
    }
    return true;
}

// Function to calculate the position index of a valid word
long long getPosition(const string& word) {
    long long position = 0;
    int wordLen = word.length();
    
    // Step 1: Count all valid words with fewer letters than the current word
    // A word of length k is essentially choosing k letters from 26 in ascending order
    // This is equivalent to C(26, k) combinations
    for (int len = 1; len < wordLen; len++) {
        position += binomial(26, len);
    }
    
    // Step 2: Count all valid words of the same length that come before this word
    // We process each position in the word from left to right
    for (int i = 0; i < wordLen; i++) {
        // Determine the starting letter for this position
        // For the first position, start from 'a' (0)
        // For subsequent positions, start from the letter after the previous position
        char startChar = (i == 0) ? 'a' : word[i-1] + 1;
        
        // Count all words where this position has a letter less than word[i]
        // but still maintaining the strictly ascending property
        for (char c = startChar; c < word[i]; c++) {
            // For each smaller character at position i, we need to choose
            // (wordLen - i - 1) more characters from the remaining letters
            // The remaining letters are those after 'c' in the alphabet
            int remainingLetters = 'z' - c;  // Number of letters after 'c'
            int remainingPositions = wordLen - i - 1;  // Positions left to fill
            
            // Add the number of valid combinations
            position += binomial(remainingLetters, remainingPositions);
        }
    }
    
    // Add 1 because we're counting positions starting from 1, not 0
    return position + 1;
}

int main() {
    string word;
    
    // Read words from input until end-of-file
    while (cin >> word) {
        // Check if the word is valid
        if (!isValid(word)) {
            cout << 0 << endl;
        } else {
            // Calculate and output the position index
            cout << getPosition(word) << endl;
        }
    }
    
    return 0;
}
