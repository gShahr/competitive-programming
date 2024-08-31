class Solution {
public:
    string stringHash(string s, int k) {
        int n = s.size();
        string ans;
        for (int i = 0; i < n/k; i++) {
            int sum = 0;
            for (int j = i*k; j < (i+1)*k; j++) {
                sum += (s[j] - 'a');
            }
            sum %= 26;
            ans += (sum + 'a');
        }
        return ans;
    }
};