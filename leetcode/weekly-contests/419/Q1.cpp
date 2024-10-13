class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        vector<int> ans;
        int n = nums.size();
        for (int i = 0; i < n-k+1; i++) {
            vector<pair<int, int>> cnt(51);
            for (int j = 0; j <= 50; j++) cnt[j] = {0, j};
            for (int j = i; j < i+k; j++) {
                cnt[nums[j]].first++;
            }
            sort(cnt.begin(), cnt.end(), greater<>());
            int sum = 0;
            // for (int j = 0; j < x; j++) cout << cnt[j].second << ' ' << cnt[j].first;
            // cout << endl;
            for (int j = 0; j < x; j++) sum += cnt[j].first * cnt[j].second;
            ans.push_back(sum);
        }
        return ans;
    }
};