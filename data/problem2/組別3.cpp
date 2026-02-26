#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string line;
    
    // Read input line by line until EOF
    while (getline(cin, line)) {
        int i = 0;
        int len = line.length();
        
        // Process each character in the line
        while (i < len) {
            // Skip whitespace characters
            if (isspace(line[i])) {
                cout << line[i];
                i++;
            }
            // Process a word (non-whitespace sequence)
            else {
                int start = i;
                
                // Find the end of the current word
                while (i < len && !isspace(line[i])) {
                    i++;
                }
                
                int end = i - 1;
                
                // Reverse and output the word
                for (int j = end; j >= start; j--) {
                    cout << line[j];
                }
            }
        }
        
        // Output newline to maintain the same number of lines
        cout << endl;
    }
    
    return 0;
}
