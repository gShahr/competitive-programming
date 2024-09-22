class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        long long int ans = 0;
        int n = word1.size();
        int m = word2.size();
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j >= m) {
                ans += (n-i);
                j = 0;
            } else if (word1[i] == word2[j]) {
                j++;
            } else {
                j = 0;
            }
        }
        return ans;
    }
};