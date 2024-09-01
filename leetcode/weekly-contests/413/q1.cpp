class Solution {
public:
    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        auto s = [](const string& c) {
            int cc = c[0]-'a'+1;
            int rr = c[1]-'0';
            return cc + rr;
        };
        int s1 = s(coordinate1);
        int s2 = s(coordinate2);
        return (s1 % 2) == (s2 % 2);
    }
};