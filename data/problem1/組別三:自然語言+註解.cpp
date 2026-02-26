#include <iostream>
#include <algorithm>
using namespace std;

/**
 * Function to calculate the cycle length for a given number n
 * Following the Collatz conjecture algorithm (3n+1 problem)
 * 
 * @param n: The starting number
 * @return: The cycle length (number of steps to reach 1, including 1)
 */
int getCycleLength(long long n) {
    int length = 1; // Start with 1 to count the initial number
    
    // Continue until we reach 1
    while (n != 1) {
        if (n % 2 == 1) {
            // If n is odd: apply 3n + 1
            n = 3 * n + 1;
        } else {
            // If n is even: divide by 2
            n = n / 2;
        }
        length++; // Increment the count for each number in the sequence
    }
    
    return length;
}

/**
 * Function to find the maximum cycle length in a range [start, end]
 * 
 * @param start: The starting value of the range
 * @param end: The ending value of the range
 * @return: The maximum cycle length found in the range
 */
int getMaxCycleLength(int start, int end) {
    int maxLength = 0;
    
    // Iterate through all numbers in the range [start, end]
    for (int i = start; i <= end; i++) {
        int currentLength = getCycleLength(i);
        maxLength = max(maxLength, currentLength);
    }
    
    return maxLength;
}

int main() {
    int i, j;
    
    // Read input pairs until EOF
    // The problem states we must process all pairs in the input
    while (cin >> i >> j) {
        // Store original values to output them in the same order
        int originalI = i;
        int originalJ = j;
        
        // Ensure start <= end for iteration
        // This handles cases where j < i
        int start = min(i, j);
        int end = max(i, j);
        
        // Calculate the maximum cycle length in the range
        int maxCycle = getMaxCycleLength(start, end);
        
        // Output the result: original i, original j, and max cycle length
        cout << originalI << " " << originalJ << " " << maxCycle << endl;
    }
    
    return 0;
}
