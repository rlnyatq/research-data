#include <iostream>
#include <stack>
#include <string>
using namespace std;

/**
 * Function to check if a string of brackets is correct
 * 
 * The algorithm uses a stack to match opening and closing brackets:
 * - When we encounter an opening bracket '(' or '[', we push it onto the stack
 * - When we encounter a closing bracket ')' or ']', we check if it matches
 *   the most recent opening bracket (top of stack)
 * - If brackets don't match or stack is empty when we need to pop, string is incorrect
 * - At the end, the stack must be empty (all brackets matched)
 * 
 * @param s The input string containing only '(', ')', '[', ']'
 * @return true if the string is correct, false otherwise
 */
bool isCorrect(const string& s) {
    stack<char> st; // Stack to keep track of opening brackets
    
    // Process each character in the string
    for (char c : s) {
        // If it's an opening bracket, push it onto the stack
        if (c == '(' || c == '[') {
            st.push(c);
        }
        // If it's a closing bracket, check for matching opening bracket
        else if (c == ')') {
            // Check if stack is empty (no matching opening bracket)
            if (st.empty()) {
                return false;
            }
            // Check if top of stack matches (should be '(')
            if (st.top() != '(') {
                return false;
            }
            // Pop the matched opening bracket
            st.pop();
        }
        else if (c == ']') {
            // Check if stack is empty (no matching opening bracket)
            if (st.empty()) {
                return false;
            }
            // Check if top of stack matches (should be '[')
            if (st.top() != '[') {
                return false;
            }
            // Pop the matched opening bracket
            st.pop();
        }
    }
    
    // String is correct only if all brackets were matched (stack is empty)
    return st.empty();
}

int main() {
    int n; // Number of test cases
    cin >> n;
    cin.ignore(); // Ignore the newline after the number
    
    // Process each test case
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s); // Read the entire line (including possible spaces)
        
        // Check if the string is correct and output the result
        if (isCorrect(s)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}

/**
 * Example trace for "([])":
 * - Read '(': stack = ['(']
 * - Read '[': stack = ['(', '[']
 * - Read ']': top is '[', matches! stack = ['(']
 * - Read ')': top is '(', matches! stack = []
 * - Stack is empty ¡÷ Output "Yes"
 * 
 * Example trace for "(([()])))":
 * - Read '(': stack = ['(']
 * - Read '(': stack = ['(', '(']
 * - Read '[': stack = ['(', '(', '[']
 * - Read '(': stack = ['(', '(', '[', '(']
 * - Read ')': matches '(', stack = ['(', '(', '[']
 * - Read ']': matches '[', stack = ['(', '(']
 * - Read ')': matches '(', stack = ['(']
 * - Read ')': matches '(', stack = []
 * - Read ')': stack is empty, no match! ¡÷ Output "No"
 * 
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(n) in worst case (all opening brackets)
 */
