class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        long long int ans = 0;
        int n = word1.size();
        int m = word2.size();
        multiset<char> l, removed;
        for (auto i: word2) l.insert(i);
        for (int i = 0; i < n; i++) {
            if (l.find(word1[i]) != l.end()) {
                l.erase(l.find(word1[i]));
                removed.insert(word1[i]);
            }
            if (l.empty()) ans += (n-i);
            if (i-m+1 >= 0) {
                if (removed.find(word1[i-m+1]) != removed.end()) {
                    l.insert(word1[i-m+1]);
                    removed.erase(removed.find(word1[i-m+1]));
                }
            }

        }
        return ans;
    }
};