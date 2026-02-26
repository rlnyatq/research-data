#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Convert ranking to ordering
vector<int> rankingToOrdering(const vector<int>& ranking) {
    int n = ranking.size();
    vector<pair<int, int>> rankEvent; // (rank, event_id)
    
    for (int i = 0; i < n; i++) {
        rankEvent.push_back({ranking[i], i + 1}); // event IDs are 1-indexed
    }
    
    sort(rankEvent.begin(), rankEvent.end());
    
    vector<int> ordering;
    for (const auto& p : rankEvent) {
        ordering.push_back(p.second);
    }
    
    return ordering;
}

// Calculate LCS length
int lcs(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    int m = b.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[n][m];
}

int main() {
    int n;
    
    while (cin >> n) {
        vector<int> correctRanking(n);
        
        // Read correct ranking
        for (int i = 0; i < n; i++) {
            cin >> correctRanking[i];
        }
        
        // Convert correct ranking to ordering
        vector<int> correctOrdering = rankingToOrdering(correctRanking);
        
        // Process each student response
        string line;
        getline(cin, line); // consume newline after n numbers
        
        while (getline(cin, line)) {
            if (line.empty()) break;
            
            vector<int> studentRanking;
            int rank;
            
            // Parse the line
            size_t pos = 0;
            while (pos < line.length()) {
                // Skip whitespace
                while (pos < line.length() && isspace(line[pos])) pos++;
                if (pos >= line.length()) break;
                
                // Read number
                int num = 0;
                while (pos < line.length() && isdigit(line[pos])) {
                    num = num * 10 + (line[pos] - '0');
                    pos++;
                }
                studentRanking.push_back(num);
            }
            
            if (studentRanking.size() != n) break;
            
            // Convert student ranking to ordering
            vector<int> studentOrdering = rankingToOrdering(studentRanking);
            
            // Calculate and print LCS
            cout << lcs(correctOrdering, studentOrdering) << endl;
        }
    }
    
    return 0;
}
