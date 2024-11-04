// class Solution {
// public:
//     int minTimeToReach(vector<vector<int>>& moveTime) {
//         int n = moveTime.size();
//         int m = moveTime[0].size();
//         int dp[n+1][m+1];
//         for (int i = 1; i <= n; i++) {
//             for (int j = 1; j <= m; j++) dp[i][j] = 0;
//         }
//         dp[0][0] = 0;
//         for (int i = 1; i <= n; i++) {
//             for (int j = 1; j <= m; j++) {
//                 dp[i][j] = max(moveTime[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
//             }
//         }
//         return dp[n][m];
//     }
// };
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // cost, cell
        pq.push({0, {0, 0}});
        set<pair<int, int>> visited;
        while (!pq.empty()) {
            auto tp = pq.top();
            pq.pop();
            if (visited.find(tp.second) != visited.end()) continue;
            visited.insert(tp.second);
            if (tp.second.first >= n-1 && tp.second.second >= m-1) return tp.first;
            if (tp.second.first > 0) {
                int cost = max(tp.first, moveTime[tp.second.first-1][tp.second.second]) + 1;
                pq.push({cost, {tp.second.first-1, tp.second.second}});
            }
            if (tp.second.second > 0) {
                int cost = max(tp.first, moveTime[tp.second.first][tp.second.second-1]) + 1;
                pq.push({cost, {tp.second.first, tp.second.second-1}});
            }
            if (tp.second.first < n-1) {
                int cost = max(tp.first, moveTime[tp.second.first+1][tp.second.second]) + 1;
                pq.push({cost, {tp.second.first+1, tp.second.second}});
            }
            if (tp.second.second < m-1) {
                int cost = max(tp.first, moveTime[tp.second.first][tp.second.second+1]) + 1;
                pq.push({cost, {tp.second.first, tp.second.second+1}});
            }
        }
        return 0;
        // for (int i = 0; i <= n; i++) {
        //     for (int j = 0; j <= m; j++) cout << dp[i][j] << ' ';
        //     cout << endl;
        // }
    }
};