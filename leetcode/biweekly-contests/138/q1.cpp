string p(int x) {
    string curr = to_string(x);
    while (curr.length() < 4) {
        curr = "0" + curr;
    }
    return curr;
}

class Solution {
public:
    int generateKey(int num1, int num2, int num3) {
        string s1, s2, s3;
        s1 = p(num1);
        s2 = p(num2);
        s3 = p(num3);
        string curr;
        for (int i = 0; i < 4; i++) {
            char mn = min({s1[i], s2[i], s3[i]});
            curr += mn;
        }
        int ans = stoi(curr);
        return ans;
    }
};