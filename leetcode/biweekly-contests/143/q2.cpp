class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        map<int, int> cnt;
        for (auto x: nums) cnt[x]++;
        int mx = *max_element(nums.begin(), nums.end());
        int offset = 1e5;
        vector<int> diff(3*offset, 0);
        for (auto x: nums) {
            diff[offset+x-k]++;
            diff[offset+x+k+1]--;
        }
        int ans = 0;
        for (int i = 1; i < diff.size(); i++) diff[i] += diff[i-1];
        for (int i = offset-k; i < offset+mx+k+1; i++) {
            int shift = diff[i] - cnt[i-offset];
            int curr = cnt[i-offset] + min(numOperations, shift);
            ans = max(curr, ans);
        }
        return ans;
    }
};

/*

cnt => exact amount
current i => exact amount + shifted

*/