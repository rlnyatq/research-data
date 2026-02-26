#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(const string& s) {
    stack<char> st;
    
    for (char ch : s) {
        // If it's an opening bracket, push it onto the stack
        if (ch == '(' || ch == '[') {
            st.push(ch);
        }
        // If it's a closing bracket
        else if (ch == ')' || ch == ']') {
            // If stack is empty, no matching opening bracket
            if (st.empty()) {
                return false;
            }
            
            char top = st.top();
            st.pop();
            
            // Check if the brackets match
            if (ch == ')' && top != '(') {
                return false;
            }
            if (ch == ']' && top != '[') {
                return false;
            }
        }
    }
    
    // If stack is empty, all brackets were matched
    return st.empty();
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline after the number
    
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        
        if (isBalanced(s)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}
