class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        vector<int> ans;
        priority_queue<int> pq;
        for (const auto& q: queries) {
            int x = q[0];
            int y = q[1];
            int d = abs(x) + abs(y);
            pq.push(d);
            if (pq.size() > k) pq.pop();
            if (pq.size() < k) ans.push_back(-1);
            else ans.push_back(pq.top());
        }
        return ans;
    }
};