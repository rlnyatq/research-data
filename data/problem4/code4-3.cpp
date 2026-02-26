#include <iostream>
#include <string>
using namespace std;

// Function to check if a word is valid (letters in strictly ascending order)
bool isValid(const string& word) {
    for (int i = 1; i < word.length(); i++) {
        if (word[i] <= word[i-1]) {
            return false;
        }
    }
    return true;
}

// Function to calculate binomial coefficient C(n, k) = n! / (k! * (n-k)!)
// This is used to count combinations
long long binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;
    
    // Use the smaller of k and n-k for efficiency
    if (k > n - k) {
        k = n - k;
    }
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Function to calculate the index of a valid word
long long getIndex(const string& word) {
    if (!isValid(word)) {
        return 0;
    }
    
    int len = word.length();
    long long index = 0;
    
    // Step 1: Count all valid words with fewer letters
    // For words of length k, we choose k letters from 26 in ascending order
    // This is equivalent to C(26, k)
    for (int k = 1; k < len; k++) {
        index += binomial(26, k);
    }
    
    // Step 2: Count valid words of the same length that come before this word
    // We process each position in the word
    for (int pos = 0; pos < len; pos++) {
        // Determine the starting letter for this position
        // If it's the first position, start from 'a' (0)
        // Otherwise, start from the letter after the previous position
        char startChar = (pos == 0) ? 'a' : (word[pos - 1] + 1);
        
        // Count how many valid words would be formed if we chose
        // a letter smaller than word[pos] at this position
        for (char ch = startChar; ch < word[pos]; ch++) {
            // If we choose 'ch' at position 'pos', we need to choose
            // (len - pos - 1) more letters from the letters after 'ch'
            int remaining = len - pos - 1;  // positions left to fill
            int available = 'z' - ch;        // letters available after ch
            
            // Add the number of ways to choose 'remaining' letters
            // from 'available' letters (all in ascending order)
            index += binomial(available, remaining);
        }
    }
    
    // Add 1 because indexing starts from 1, not 0
    return index + 1;
}

int main() {
    string word;
    
    // Read input until EOF
    while (cin >> word) {
        // Calculate and output the index for each word
        cout << getIndex(word) << endl;
    }
    
    return 0;
}
