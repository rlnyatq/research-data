#include <iostream>
#include <algorithm>
using namespace std;

// Function to calculate the cycle length for a given number
int getCycleLength(long long n) {
    int length = 1;
    while (n != 1) {
        if (n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        length++;
    }
    return length;
}

// Function to find the maximum cycle length in a range
int getMaxCycleLength(int i, int j) {
    int minVal = min(i, j);
    int maxVal = max(i, j);
    int maxLength = 0;
    
    for (int n = minVal; n <= maxVal; n++) {
        int cycleLength = getCycleLength(n);
        maxLength = max(maxLength, cycleLength);
    }
    
    return maxLength;
}

int main() {
    int i, j;
    
    // Read pairs of integers until EOF
    while (cin >> i >> j) {
        int maxCycleLength = getMaxCycleLength(i, j);
        
        // Output in the same order as input
        cout << i << " " << j << " " << maxCycleLength << endl;
    }
    
    return 0;
}
