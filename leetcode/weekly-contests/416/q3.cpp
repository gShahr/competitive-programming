class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        long long int ans = 0;
        int n = word1.size();
        int m = word2.size();
        multiset<char> words, removed;
        for (auto i: word2) words.insert(i);
        int l = 0;
        int r = 0;
        while (r < n) {
            while (r < n && !words.empty()) {
                if (words.find(word1[r]) != words.end()) {
                    words.erase(words.find(word1[r]));
                    removed.insert(word1[r]);
                }
                r++;
            }
            if (words.empty()) ans += (n - r + 1);
            if (removed.find(word1[l]) != removed.end()) {
                words.insert(word1[l]);
                removed.erase(removed.find(word1[l]));
            }
            l++;
        }
        return ans;
    }
};