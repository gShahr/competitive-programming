class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        vector<int> ans;
        map<int, int> cnt;
        for (auto i: nums) cnt[i]++;
        for (auto i: cnt) {
            if (i.second >= 2) {
                ans.push_back(i.first);
            }
        }
        return ans;
    }
};