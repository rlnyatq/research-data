#include <iostream>
#include <string>
#include <stack>
using namespace std;

/**
 * Function to check if a string is a "correct string" according to the given rules.
 * 
 * The rules define a correct string recursively:
 * 1. Empty string is correct
 * 2. Concatenation of two correct strings is correct
 * 3. If A is correct, then (A) and [A] are correct
 * 
 * This is equivalent to checking balanced parentheses/brackets where:
 * - Every opening bracket has a matching closing bracket
 * - Brackets are properly nested (no crossing)
 * - Different types of brackets match correctly: '(' with ')' and '[' with ']'
 * 
 * Algorithm: Use a stack to track opening brackets
 * - Push opening brackets onto stack
 * - When encountering closing bracket, check if it matches the top of stack
 * - If mismatch or stack empty when we need a match, string is incorrect
 * - At end, stack must be empty (all brackets matched)
 */
bool isCorrectString(const string& s) {
    // Stack to keep track of opening brackets
    stack<char> st;
    
    // Process each character in the string
    for (char c : s) {
        // If it's an opening bracket, push it onto the stack
        if (c == '(' || c == '[') {
            st.push(c);
        }
        // If it's a closing bracket, we need to match it
        else if (c == ')' || c == ']') {
            // If stack is empty, we have a closing bracket with no matching opening
            if (st.empty()) {
                return false;
            }
            
            // Get the top opening bracket
            char top = st.top();
            st.pop();
            
            // Check if the brackets match:
            // '(' should match with ')'
            // '[' should match with ']'
            if ((c == ')' && top != '(') || (c == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    // After processing all characters, stack should be empty
    // If not empty, we have unmatched opening brackets
    return st.empty();
}

int main() {
    // Optimize input/output for faster processing
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read the number of strings to process
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline after the integer
    
    // Process each string
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s); // Read the entire line (handles empty strings too)
        
        // Check if the string is correct and output result
        if (isCorrectString(s)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
