bool solve(int i, int j) {
    solve(i-1, j)
}

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int mx = 100;
        int dp[n+1][m+1][mx+1];
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= m; k++) {
                    // check dp[i-1][k][i]
                    bool ok = true;
                    for (int l = 1; l <= mx; l++) {
                        if (dp[i-1][k][l] == grid[i-1][j-1]) ok = false;
                    }
                    int sum = 0;
                    if (ok) sum += grid[i-1][j-1];
                    for (int l = 1; l <= mx; l++) sum += dp[i-1][k][l];
                    int currSum = 0;
                    for (int l = 1; l <= mx; l++) currSum += dp[i][j][l];
                    if (sum > currSum) {
                        for (int l = 1; l <= mx; l++) dp[i][j][l] = 0;
                        for (int l = 1; l <= mx; l++) dp[i][j][l] = dp[i-1][k][l];
                        dp[i][j][grid[i-1][j-1]] = grid[i-1][j-1];
                    }
                }
            }
        }
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) cout << dp[i][j][1] << ' ';
        //     cout << endl;
        // }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            int curr = 0;
            for (int j = 1; j <= mx; j++) curr += dp[n][i][j];
            ans = max(ans, curr);
        }
        return ans;
    }
};

/*

get prev value that is max that is not same value as it
=> inductive argument

i rows => 1 dp table
dp[i][j] = dp[i-1] 

ith row with numbers taken
max sum that can be achieved

max value
taken values
curr cell

greatest sum that doesn't contain grid[i][j]

*/