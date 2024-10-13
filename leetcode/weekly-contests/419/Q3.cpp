int winner(char aliceSummon, char bobSummon) {
    if (aliceSummon == bobSummon) return 0;  // Draw case
    if ((aliceSummon == 'W' && bobSummon == 'F') || 
        (aliceSummon == 'F' && bobSummon == 'E') || 
        (aliceSummon == 'E' && bobSummon == 'W')) {
        return -1;  // Alice wins
    }
    return 1;  // Bob wins
}

int totalBobWins(const string& aliceMoves, long long m) {
    int n = aliceMoves.size();
    // rounds, last move, bob-points
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(3, vector<int>(2 * n + 1, -1)));
    function<int(int, int, int)> countWays = [&](int round, char lastMove, int bobPoints) -> int {
        if (round == n) { // Base case: last round
            return (bobPoints > n) ? 1 : 0;
        }
        auto moveToInt = [](char c) {
            if (c == 'W') return 0;
            if (c == 'F') return 1;
            return 2;
        };
        if (dp[round][moveToInt(lastMove)][bobPoints] != -1) return dp[round][moveToInt(lastMove)][bobPoints];
        long long int totalWays = 0;
        vector<char> elements = {'W', 'F', 'E'};
        for (char bobMove : elements) {
            if (bobMove == lastMove) continue;  // Bob can't play the same move consecutively
            int result = winner(aliceMoves[round], bobMove);
            totalWays = (totalWays + countWays(round + 1, bobMove, bobPoints + result)) % m;
        }
        return dp[round][moveToInt(lastMove)][bobPoints] = totalWays;
    };
    return countWays(0, 'o', n);
}

class Solution {
public:
    int countWinningSequences(string s) {
        int mod = 1e9 + 7;
        int ans = totalBobWins(s, mod);
        return ans;
    }
};

/*

F G => F
W F => W
E W => E
X X => 0

count all sequences which bob beats alice and remove the sequences with repeated
elements

*/