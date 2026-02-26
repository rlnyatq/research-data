#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    string line;
    
    // Read each line from input until EOF
    while (getline(cin, line)) {
        // Create a string stream to parse words from the line
        stringstream ss(line);
        string word;
        bool firstWord = true;
        
        // Extract each word from the line
        while (ss >> word) {
            // Add space before each word except the first one
            // This preserves the single-space separation in output
            if (!firstWord) {
                cout << " ";
            }
            firstWord = false;
            
            // Reverse the characters in the current word
            // The reverse function from <algorithm> reverses elements in-place
            // between the begin() and end() iterators
            reverse(word.begin(), word.end());
            
            // Output the reversed word
            cout << word;
        }
        
        // Print newline after each line to preserve line structure
        cout << endl;
    }
    
    return 0;
}
