class Solution {
public:
    int maxScore(std::vector<int>& a, std::vector<int>& b) {
        int n = b.size();
        vector<vector<long long int>> dp(5, vector<long long int>(n+1, -1e9));
        for (int j = 0; j <= n; j++) dp[0][j] = 0;
        for (int i = 1; i <= 4; i++) {
            for (int j = i; j <= n; j++) dp[i][j] = max(dp[i][j-1], dp[i-1][j-1] + (long long int)a[i-1] * b[j-1]);
        }
        return dp[4][n];
    }
};