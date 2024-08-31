unordered_set<string> uniquePalindromes;
long long factorial[100];

void computeF() {
    for (long long i = 2; i <= 10; i++) {
        factorial[i] = factorial[i-1] * i;
    }
}

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        generatePalindromes(n, k);
        factorial[0] = 1;
        factorial[1] = 1;
        computeF();
        long long ans = 0;
        for (const auto& palindrome: uniquePalindromes) {
            ans += countPermutations(palindrome);
        }
        uniquePalindromes.clear();
        return ans;
    }

    void generatePalindromes(int n, int k) {
        int halfLength = (n+1)/2;
        for (int i = 1; i <= 9; i++) {
            generatePalindromesHelper(i, halfLength-1, n, k);
        }
    }

    void generatePalindromesHelper(long long current, int remainingDigits, int n, int k) {
        if (remainingDigits == 0) {
            string palindrome = createPalindrome(current, n);
            if (stoll(palindrome) % k == 0) {
                sort(palindrome.begin(), palindrome.end());
                uniquePalindromes.insert(palindrome);
            }
            return;
        }
        for (int i = 0; i <= 9; i++) {
            generatePalindromesHelper(current*10 + i, remainingDigits-1, n, k);
        }
    }

    string createPalindrome(long long half, int n) {
        string halfStr = to_string(half);
        string reverseHalf = halfStr;
        reverse(reverseHalf.begin(), reverseHalf.end());
        string nw;
        if (n % 2 == 0) nw = halfStr + reverseHalf;
        else nw = halfStr + reverseHalf.substr(1);
        return nw;
    }

    long long countPermutations(string palindrome) {
        vector<int> digitCount(10, 0);
        int n = palindrome.size();

        for (char c: palindrome) {
            digitCount[c-'0']++;
        }
        long long totalPermutations = factorial[n];
        for (int count: digitCount) {
            totalPermutations /= factorial[count];
        }
        long long validPermutations = totalPermutations;
        if (digitCount[0] > 0) {
            digitCount[0]--;
            long long invalidPermutations = factorial[n-1];
            for (int count: digitCount) {
                invalidPermutations /= factorial[count];
            }
            validPermutations -= invalidPermutations;
        }
        return validPermutations;
    }
};

/*

Find all palindromes of length n
    - Only count unique palindromes divisible by k
Count permutations of each unique palindrome and add them up
    - Special case if they include 0 as 0 cannot be placed in the front

For example:
    - 551 has 3 permutations that are good (155, 515, 551)

*/