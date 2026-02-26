#include <iostream>
#include <string>
using namespace std;

// Calculate C(n, k) - combinations
long long combination(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;
    
    // Use the smaller of k and n-k for efficiency
    if (k > n - k) k = n - k;
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

bool isValid(const string& word) {
    for (int i = 1; i < word.length(); i++) {
        if (word[i] <= word[i-1]) {
            return false;
        }
    }
    return true;
}

long long getPosition(const string& word) {
    if (!isValid(word)) {
        return 0;
    }
    
    int len = word.length();
    long long position = 0;
    
    // Add all valid words with fewer letters
    for (int i = 1; i < len; i++) {
        position += combination(26, i);
    }
    
    // Now count valid words of the same length that come before this word
    // Convert letters to 0-indexed positions
    int prevPos = -1;  // Track the previous letter position
    
    for (int i = 0; i < len; i++) {
        int currentPos = word[i] - 'a';
        
        // Count all valid words where position i has a smaller letter
        // The letter at position i must be > prevPos and < currentPos
        for (int letterPos = prevPos + 1; letterPos < currentPos; letterPos++) {
            // If we choose letterPos at position i, we need to choose (len - i - 1)
            // more letters from the remaining letters after letterPos
            int remaining = len - i - 1;  // How many more letters we need
            int available = 26 - letterPos - 1;  // Letters after letterPos
            position += combination(available, remaining);
        }
        
        prevPos = currentPos;
    }
    
    // Add 1 because positions are 1-indexed
    position += 1;
    
    return position;
}

int main() {
    string word;
    while (cin >> word) {
        cout << getPosition(word) << endl;
    }
    return 0;
}
