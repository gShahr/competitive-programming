class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // algo taken from https://codeforces.com/blog/entry/126241
        vector<vector<int>> divisors(int(5 * 1e4 + 1));
        for (int i = 1; i <= int(5 * 1e4); i++) {
            for (int j = i; j <= int(5 * 1e4); j += i) {
                divisors[j].push_back(i);
            }
        }
        vector<int> frequency(int(5 * 1e4 + 1), 0);
        for (int i = 0; i < nums.size(); i++) {
            frequency[nums[i]]++;
        }
        vector<int> dp(int(5 * 1e4 + 1), 0);
        for (int i = 5 * 1e4; i >= 1; i--) {
            long long sum = 0;
            for (int j = i; j <= int(5 * 1e4); j += i) {
                sum += frequency[j];
            }
            sum = (sum * sum - sum) >> 1ll;
            for (int j = i + i; j <= int(5 * 1e4); j += i) {
                sum -= dp[j];
            }
            dp[i] = sum;
        }
        for (int i = 1; i < dp.size(); i++) dp[i] += dp[i-1];
        // for (int i = 0; i < 10; i++) cout << dp[i] << ' ';
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            int q = queries[i];
            int res = lower_bound(dp.begin(), dp.end(), q+1) - dp.begin();
            ans.push_back(res);
        }
        return ans;
    }
};