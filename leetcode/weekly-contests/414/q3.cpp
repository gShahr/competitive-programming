class Solution {
public:
    long long findMaximumScore(std::vector<int>& nums) {
        int n = nums.size();
        long long int curr = nums[0];
        int ind = 0;
        long long int ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > curr) {
                ans += (curr * (i-ind));
                curr = nums[i];
                ind = i;
            }
        }
        if (ind < n-1) ans += (curr * (n-1-ind));
        return ans;
    }
};

/*

a[0] * x + d[0]

a[0] * x+1 + dp[0]
a[1] * x + dp[1]

a[0] * x+2 + dp[0]
a[1] * x+1 + dp[1]
a[2] * x + dp[2]

a[0] * x + dp[0]
a[1] * x-1 + dp[1]
a[2] * x-2 + dp[2]
a[3] * x-3 + dp[3]

6 6
9 12
5 1 2
4 3 2

Misread nums[i] as nums[j] and got confused on how to solve in O(nlogn) or faster. But
if it's using nums[i], then just select greater value and iterate (greedy solution). 

*/