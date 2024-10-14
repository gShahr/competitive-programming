class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        vector<long long> ans;
        map<int, int> cnt;
        int n = nums.size();
        set<pair<int, int>> top_num, top_freq, bottom_num, bottom_freq;
        int sum = 0;
        for (int i = 0; i < k; i++) {
            // add nums[i]
            if (top_num.size() < x) {
                auto it = top_num.lower_bound({nums[i], -1});
                if (it != top_num.end() && it->first == nums[i]) {
                    pair<int, int> nw = {it->first, it->second+1}; // num, freq
                    top_num.erase(it);
                    top_num.insert(nw);
                    auto freq_it = top_freq.lower_bound({nw.second-1, nw.first});
                    nw = {nw.second, nw.first}; // freq, num
                    top_freq.erase(freq_it);
                    top_freq.insert(nw);
                } else {
                    pair<int, int> nw = {nums[i], 1};
                    top_num.insert(nw);
                    nw = {1, nums[i]};
                    top_freq.insert(nw);
                }
                cnt[nums[i]]++;
                sum += nums[i];
            } else {
                
            }
        }
        ans.push_back(sum);
        for (int i = k; i < n; i++) {
            // remove nums[i-k]
            // add nums[i]
            ans.push_back(sum);
        }
        return ans;
    }
};

/*



*/