bool check(map<char, int>& cnt1, map<char, int>& cnt2) {
    for (char i = 'a'; i <= 'z'; i++) {
        if (cnt1[i] < cnt2[i]) return false;
    }
    return true;
}

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        long long int ans = 0;
        int n = word1.size();
        int m = word2.size();
        map<char, int> cnt1, cnt2;
        for (char i = 'a'; i <= 'z'; i++) cnt1[i] = 0;
        for (char i = 'a'; i <= 'z'; i++) cnt2[i] = 0;
        for (auto i: word2) cnt2[i]++;
        int l = 0;
        int r = 0;
        while (l < n && r <= n) {
            while (r < n && !check(cnt1, cnt2)) {
                cnt1[word1[r]]++;
                r++;
            }
            if (check(cnt1, cnt2)) ans += (n - r + 1);
            cnt1[word1[l]]--;
            l++;
        }
        return ans;
    }
};