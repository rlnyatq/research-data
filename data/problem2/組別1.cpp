#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    string line;
    
    // Read input line by line until EOF
    while (getline(cin, line)) {
        string result = "";
        string currentWord = "";
        
        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            
            // Check if character is whitespace
            if (isspace(c)) {
                // If we have accumulated a word, reverse it and add to result
                if (!currentWord.empty()) {
                    reverse(currentWord.begin(), currentWord.end());
                    result += currentWord;
                    currentWord = "";
                }
                // Add the whitespace character
                result += c;
            } else {
                // Accumulate non-whitespace characters
                currentWord += c;
            }
        }
        
        // Don't forget the last word if line doesn't end with whitespace
        if (!currentWord.empty()) {
            reverse(currentWord.begin(), currentWord.end());
            result += currentWord;
        }
        
        cout << result << endl;
    }
    
    return 0;
}
