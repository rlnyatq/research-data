/**
 * Word Character Reversal Program
 * 
 * This program reads lines of text from standard input and reverses the characters
 * within each word while preserving:
 * - The number of lines
 * - The number of words per line
 * - The order of words in each line
 * - The exact spacing and whitespace between words
 * 
 * A word is defined as a maximal contiguous sequence of non-whitespace characters.
 * Whitespace includes spaces, tabs, and other whitespace characters.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

/**
 * Checks if a character is whitespace.
 * 
 * @param c The character to check
 * @return true if the character is whitespace, false otherwise
 */
bool isWhitespace(char c) {
    return isspace(static_cast<unsigned char>(c));
}

/**
 * Processes a single line of text by reversing the characters within each word
 * while preserving all whitespace exactly as it appears in the original line.
 * 
 * Algorithm:
 * 1. Iterate through the line character by character
 * 2. When a non-whitespace character is found, mark the start of a word
 * 3. Continue until whitespace or end of line is found, marking the end of the word
 * 4. Reverse the characters within the word boundaries
 * 5. Continue with the next word
 * 
 * @param line The input line to process (passed by reference, modified in place)
 */
void processLine(string& line) {
    int n = line.length();
    int i = 0;
    
    // Iterate through the entire line
    while (i < n) {
        // Skip whitespace characters - these are preserved as-is
        if (isWhitespace(line[i])) {
            i++;
            continue;
        }
        
        // Found the start of a word
        int wordStart = i;
        
        // Find the end of the word by advancing until we hit whitespace or end of line
        while (i < n && !isWhitespace(line[i])) {
            i++;
        }
        
        // Now we have a word from wordStart to (i-1)
        int wordEnd = i - 1;
        
        // Reverse the characters within this word using two pointers
        // Left pointer starts at the beginning of the word
        // Right pointer starts at the end of the word
        // Swap characters and move pointers toward center until they meet
        int left = wordStart;
        int right = wordEnd;
        
        while (left < right) {
            // Swap characters at left and right positions
            swap(line[left], line[right]);
            left++;
            right--;
        }
        
        // After reversing, i is already positioned at the whitespace
        // or end of string, so the loop will continue naturally
    }
}

/**
 * Main function - Entry point of the program
 * 
 * Reads lines from standard input until EOF, processes each line to reverse
 * the characters within words, and outputs the transformed lines.
 * 
 * Edge cases handled:
 * - Empty lines (preserved as empty lines)
 * - Lines with only whitespace (preserved as-is)
 * - Lines with leading/trailing whitespace (preserved exactly)
 * - Multiple consecutive spaces/tabs (preserved exactly)
 * - Single character words (remain unchanged)
 * - Lines with only one word
 * - Empty input (produces empty output)
 */
int main() {
    string line;
    
    // Read input line by line using getline to preserve all whitespace
    // getline reads until newline character, preserving spaces and tabs
    while (getline(cin, line)) {
        // Process the line in-place (reverse characters within each word)
        processLine(line);
        
        // Output the transformed line
        cout << line << endl;
    }
    
    return 0;
}
