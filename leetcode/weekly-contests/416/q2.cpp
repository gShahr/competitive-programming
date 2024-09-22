bool check2(long long int j, int workerTime, long long int x) {
    __int128 sum = (__int128)j * (j + 1) / 2 * workerTime;
    return sum <= x;
}

bool check(long long int x, int mountainHeight, vector<int>& workerTimes) {
    int n = workerTimes.size();
    for (int i = 0; i < n; i++) {
        long long int j = 0;
        for (long long int b = 1e9; b >= 1; b /= 2) {
            while (check2(j+b, workerTimes[i], x)) j += b;
        }
        mountainHeight -= j;
    }
    return mountainHeight > 0;
}

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long int x = 0;
        for (long long int b = 1e9; b >= 1; b /= 2) {
            while (check(x+b, mountainHeight, workerTimes)) x += b;
        }
        return x+1;
    }
};