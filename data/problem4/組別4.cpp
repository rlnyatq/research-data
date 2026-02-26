#include <iostream>
#include <string>
using namespace std;

// Precomputed binomial coefficients C(n, k) for n = 0 to 26, k = 0 to 5
// C(n, k) represents the number of ways to choose k items from n items
long long C[27][6];

// Function to precompute binomial coefficients using dynamic programming
// C(n, k) = C(n-1, k-1) + C(n-1, k)
// Base cases: C(n, 0) = 1 for all n, C(0, k) = 0 for k > 0
void precomputeBinomial() {
    // Initialize base cases
    for (int n = 0; n <= 26; n++) {
        C[n][0] = 1;  // Choosing 0 items from n items: exactly 1 way (choose nothing)
    }
    
    // Fill the table using Pascal's triangle recurrence
    for (int n = 1; n <= 26; n++) {
        for (int k = 1; k <= 5; k++) {
            if (k > n) {
                C[n][k] = 0;  // Cannot choose more items than available
            } else {
                C[n][k] = C[n-1][k-1] + C[n-1][k];
            }
        }
    }
}

// Function to check if a word is valid (strictly increasing character positions)
// A word is valid if f(w?) < f(w?) < ... < f(w?)
bool isValid(const string& word) {
    for (int i = 1; i < word.length(); i++) {
        if (word[i] <= word[i-1]) {  // Characters must be strictly increasing
            return false;
        }
    }
    return true;
}

// Function to compute the index I(w) for a valid word w
// The index represents the position of w in the lexicographically ordered set V
long long computeIndex(const string& word) {
    int k = word.length();  // Length of the word
    long long index = 0;
    
    // Step 1: Count all valid words of length less than k
    // These words come before any word of length k in lexicographic order
    for (int len = 1; len < k; len++) {
        index += C[26][len];  // C(26, len) = number of valid words of length len
    }
    
    // Step 2: Count valid words of length k that come before the current word
    // We process each position of the word from left to right
    int prevChar = 0;  // Track the previous character position (0 means no previous char)
    
    for (int pos = 0; pos < k; pos++) {
        int currentChar = word[pos] - 'a' + 1;  // Convert character to position (1-26)
        
        // Count all valid words that:
        // - Have the same prefix up to position (pos-1)
        // - Have a character smaller than word[pos] at position pos
        // - Maintain the strictly increasing property
        
        // The character at position pos must be:
        // - Greater than prevChar (to maintain increasing order)
        // - Less than currentChar (to come before current word lexicographically)
        
        for (int ch = prevChar + 1; ch < currentChar; ch++) {
            // If we place character ch at position pos, we need to fill
            // the remaining (k - pos - 1) positions with characters > ch
            // The number of available characters is (26 - ch)
            int remaining = k - pos - 1;  // Remaining positions to fill
            int available = 26 - ch;       // Available characters (ch+1 to 26)
            
            if (remaining <= available) {
                index += C[available][remaining];
            }
        }
        
        prevChar = currentChar;  // Update previous character for next iteration
    }
    
    // Step 3: Add 1 because indexing starts from 1, not 0
    index += 1;
    
    return index;
}

int main() {
    // Precompute binomial coefficients once at the start
    precomputeBinomial();
    
    string word;
    
    // Read input words until end-of-file
    while (cin >> word) {
        // Check if the word is valid
        if (!isValid(word)) {
            cout << 0 << endl;  // Invalid word: output 0
        } else {
            // Valid word: compute and output its index
            cout << computeIndex(word) << endl;
        }
    }
    
    return 0;
}
