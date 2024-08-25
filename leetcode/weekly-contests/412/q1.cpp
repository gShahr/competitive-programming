class Solution {
public:
    std::vector<int> getFinalState(std::vector<int>& nums, int k, int multiplier) {
        for (int i = 0; i < k; ++i) {
            auto min_it = std::min_element(nums.begin(), nums.end());
            *min_it *= multiplier;
        }
        return nums;
    }
};