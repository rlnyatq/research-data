#include <iostream>
#include <string>
#include <stack>
using namespace std;

/**
 * Function to check if a string of parentheses is balanced
 * 
 * Algorithm:
 * - Use a stack to track opening brackets
 * - For each opening bracket '(' or '[', push it onto the stack
 * - For each closing bracket ')' or ']', check if it matches the top of stack
 * - If stack is empty at the end, the string is balanced
 * 
 * @param s: The string to check
 * @return: true if balanced, false otherwise
 */
bool isBalanced(const string& s) {
    stack<char> st;  // Stack to store opening brackets
    
    // Iterate through each character in the string
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        
        // If it's an opening bracket, push it onto the stack
        if (ch == '(' || ch == '[') {
            st.push(ch);
        }
        // If it's a closing bracket, check for matching opening bracket
        else if (ch == ')') {
            // If stack is empty or top doesn't match, it's unbalanced
            if (st.empty() || st.top() != '(') {
                return false;
            }
            st.pop();  // Remove the matching opening bracket
        }
        else if (ch == ']') {
            // If stack is empty or top doesn't match, it's unbalanced
            if (st.empty() || st.top() != '[') {
                return false;
            }
            st.pop();  // Remove the matching opening bracket
        }
    }
    
    // String is balanced only if all brackets were matched (stack is empty)
    return st.empty();
}

int main() {
    int n;  // Number of test strings
    cin >> n;
    cin.ignore();  // Ignore the newline after reading the number
    
    // Process each test string
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);  // Read the entire line (handles empty strings too)
        
        // Check if the string is balanced and output result
        if (isBalanced(line)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}
