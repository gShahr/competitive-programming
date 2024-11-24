#include <vector>
using namespace std;

vector<int> sieve(int n) {
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) d[i] = i;
    for(int i = 2; i * i <= n; i++) {
        if(d[i] == i) {
            for(int j = i * i; j <= n; j += i) {
                d[j] = i;
            }
        }
    }
    return d;
}