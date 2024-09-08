bool check(long long int x, vector<int>& start, int d) {
    bool ok = true;
    long long int curr = start[0];
    for (int i = 1; i < start.size(); i++) {
        long long int next = curr + x;
        if (next > start[i] + d) {
            ok = false;
            break;
        }
        curr = max(next, (long long int)start[i]);
    }
    return ok;
}

class Solution {
public:
    int maxPossibleScore(vector<int>& start, int d) {
        sort(start.begin(), start.end());
        int ans = 0;
        for (int i = 1e9; i >= 1; i /= 2) {
            while (check((long long int)ans + i, start, d)) ans += i;
        }
        return ans;
    }
};