#include <iostream>
#include <algorithm>
using namespace std;

/**
 * Computes the cycle length for a given number n according to the 3n+1 algorithm
 * (also known as the Collatz conjecture or hailstone sequence).
 * 
 * The algorithm repeatedly applies:
 * - If n is odd: n = 3n + 1
 * - If n is even: n = n / 2
 * - Stop when n = 1
 * 
 * @param n The starting number (must be positive)
 * @return The number of steps (cycle length) until reaching 1, including 1
 */
int getCycleLength(long long n) {
    int length = 1; // Start counting from the initial number
    
    // Continue until we reach 1
    while (n != 1) {
        if (n % 2 == 1) {
            // n is odd: apply 3n + 1
            n = 3 * n + 1;
        } else {
            // n is even: divide by 2
            n = n / 2;
        }
        length++; // Increment the cycle length for each step
    }
    
    return length;
}

/**
 * Finds the maximum cycle length for all integers in the range [i, j].
 * This function handles the case where i > j by automatically swapping them.
 * 
 * @param i First boundary of the range
 * @param j Second boundary of the range
 * @return The maximum cycle length found in the range
 */
int getMaxCycleLength(int i, int j) {
    // Determine the actual min and max to handle cases where i > j
    int minVal = min(i, j);
    int maxVal = max(i, j);
    
    int maxLength = 0;
    
    // Iterate through all numbers in the range [minVal, maxVal]
    for (int n = minVal; n <= maxVal; n++) {
        int currentLength = getCycleLength(n);
        maxLength = max(maxLength, currentLength);
    }
    
    return maxLength;
}

int main() {
    int i, j;
    
    // Read pairs of integers until EOF
    while (cin >> i >> j) {
        // Compute the maximum cycle length for the range
        int maxCycleLength = getMaxCycleLength(i, j);
        
        // Output: original i, original j, and the maximum cycle length
        // Important: Output i and j in the same order as input
        cout << i << " " << j << " " << maxCycleLength << endl;
    }
    
    return 0;
}
