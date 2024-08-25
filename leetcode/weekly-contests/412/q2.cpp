bool check(int x, int y) {
    string sx = to_string(x);
    string sy = to_string(y);    
    while (sx.size() < sy.size()) {
        sx.insert(sx.begin(), '0');
    }
    while (sy.size() < sx.size()) {
        sy.insert(sy.begin(), '0');
    }
    int n = sx.size();
    int cnt = 0;
    pair<int, int> a1 = {-1, -1};
    pair<int, int> a2 = {-1, -1};
    for (int i = 0; i < n; i++) {
        if (sx[i] != sy[i]) {
            if (a1.first == -1) {
                a1.first = sx[i] - '0';
                a1.second = sy[i] - '0';
            } else {
                a2.first = sx[i] - '0';
                a2.second = sy[i] - '0';
            }
            cnt++;
        }
    }
    // cout << sx << ' ' << sy << ' ' << a1.first << ' ' << a1.second << ' ' << a2.first << ' ' << a2.second << endl;
    return cnt <= 2 && a1.first == a2.second && a1.second == a2.first;
}

class Solution {
public:
    int countPairs(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (check(nums[i], nums[j])) ans++;
            }
        }
        return ans;
    }
};