// taken from https://www.geeksforgeeks.org/maximum-number-of-overlapping-intervals/
// Function that returns maximum
// overlap among ranges
int overlap(vector<pair<int, int>> v) {
    // variable to store the maximum
    // count
    int ans = 0;
    int count = 0;
    vector<pair<int, char> > data;

    // storing the x and y
    // coordinates in data vector
    for (int i = 0; i < v.size(); i++) {

        // pushing the x coordinate
        data.push_back({ v[i].first, 'x' });

        // pushing the y coordinate
        data.push_back({ v[i].second, 'y' });
    }

    // sorting of ranges
    sort(data.begin(), data.end());

    // Traverse the data vector to
    // count number of overlaps
    for (int i = 0; i < data.size(); i++) {

        // if x occur it means a new range
        // is added so we increase count
        if (data[i].second == 'x')
            count++;

        // if y occur it means a range
        // is ended so we decrease count
        if (data[i].second == 'y')
            count--;

        // updating the value of ans
        // after every traversal
        ans = max(ans, count);
    }
    return ans;
}


class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        map<int, int> cnt;
        for (auto x: nums) cnt[x]++;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = lower_bound(nums.begin(), nums.end(), nums[i] - k) - nums.begin();
            int y = upper_bound(nums.begin(), nums.end(), nums[i] + k) - nums.begin();
            y--;
            int total = y-x+1;
            int shift = total - cnt[nums[i]];
            int curr = cnt[nums[i]] + min(numOperations, shift);
            ans = max(curr, ans);
        }
        cout << ans << endl;
        vector<pair<int, int>> p;
        for (auto x: nums) {
            pair<int, int> curr = {x-k, x+k};
            p.push_back(curr);
        }
        ans = max(ans, min(numOperations, overlap(p)));
        return ans;
    }
};

// map<int, int> cnt;
// for (auto x: nums) cnt[x]++;
// int mx = *max_element(nums.begin(), nums.end());
// int offset = 1e5;
// vector<int> diff(3*offset, 0);
// for (auto x: nums) {
//     diff[offset+x-k]++;
//     diff[offset+x+k+1]--;
// }
// int ans = 0;
// for (int i = 1; i < diff.size(); i++) diff[i] += diff[i-1];
// for (int i = offset-k; i < offset+mx+k+1; i++) {
//     int shift = diff[i] - cnt[i-offset];
//     int curr = cnt[i-offset] + min(numOperations, shift);
//     ans = max(curr, ans);
// }
// return ans;