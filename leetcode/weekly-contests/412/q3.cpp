long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        int MOD = 1e9+7;
        int n = nums.size();
        using pii = std::pair<long long int, long long int>;
        auto cmp = [](const pii& a, const pii& b) {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first > b.first;
        };
        std::priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        set<int> visited;
        map<int, int> cnt;
        int kP = -1;
        for (int i = 0; i < n; ++i) {
            pq.emplace(nums[i], i);
        }
        int last = -1;
        for (int i = 1; i <= k; i++) {
            auto tp = pq.top();
            pq.pop();
            long long int mn = tp.first;
            mn = (mn * multiplier) % MOD;
            pq.push({mn, tp.second});
            cnt[tp.second]++;
            visited.insert(tp.second);
            if (visited.size() >= n) {
                kP = i;
                last = tp.second;
                break;
            }
        }
        while (kP < k && pq.top().second == last) {
            auto tp = pq.top();
            pq.pop();
            long long int mn = tp.first;
            mn = (mn * multiplier) % MOD;
            pq.push({mn, tp.second});
            cnt[tp.second]++;
            kP++;
        }
        std::vector<int> ans(n);
        while (!pq.empty()) {
            auto tp = pq.top();
            pq.pop();
            ans[tp.second] = tp.first;
        }
        // for (auto i: ans) cout << i << ' ';
        // cout << endl;
        vector<pair<int, int>> order;
        for (int i = 0; i < ans.size(); i++) {
            order.emplace_back(ans[i], i);
        }
        sort(order.begin(), order.end());
        int left = k - kP;
        int extraOperations = left % kP;
        for (int i = 0; i < n; i++) {
            int j = order[i].second;
            cout << j << endl;
            int use = min(extraOperations, cnt[j]);
            extraOperations -= use;
            int res = (ans[j] * binpow(multiplier, cnt[j] * left/kP + use, MOD)) % MOD;
            ans[j] = res;
        }
        return ans;
    }
};