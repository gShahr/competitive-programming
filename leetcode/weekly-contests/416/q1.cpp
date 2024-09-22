class Solution {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        set<string> banned;
        for (auto i: bannedWords) banned.insert(i);
        int cnt = 0;
        for (auto i: message) {
            if (banned.find(i) != banned.end()) cnt++;
        }
        return cnt >= 2;
    }
};