#ifndef DEBUG_TEMPLATE_CPP
#define DEBUG_TEMPLATE_CPP
//#include <bits/stdc++.h>
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
using namespace std;
// #define cerr cout
namespace __DEBUG_UTIL__
{
    using namespace std;
    bool I_want_colored_output = true; /* ONLY WORKS WITH TERMINAL */
    string white = I_want_colored_output ? "\033[0;m" : "";
    string outer = I_want_colored_output ? "\033[0;31m" : "";    // red
    string varName = I_want_colored_output ? "\033[1;34m" : "";  // blue
    string varValue = I_want_colored_output ? "\033[1;32m" : ""; // green

    /* Primitive Datatypes Print */
    void print(const char *x) { cerr << x; }
    void print(bool x) { cerr << (x ? "T" : "F"); }
    void print(char x) { cerr << '\'' << x << '\''; }
    void print(signed short int x) { cerr << x; }
    void print(unsigned short int x) { cerr << x; }
    void print(signed int x) { cerr << x; }
    void print(unsigned int x) { cerr << x; }
    void print(signed long int x) { cerr << x; }
    void print(unsigned long int x) { cerr << x; }
    void print(signed long long int x) { cerr << x; }
    void print(unsigned long long int x) { cerr << x; }
    void print(float x) { cerr << x; }
    void print(double x) { cerr << x; }
    void print(long double x) { cerr << x; }
    void print(string x) { cerr << '\"' << x << '\"'; }
    template <size_t N>
    void print(bitset<N> x) { cerr << x; }
    void print(vector<bool> v)
    { /* Overloaded this because stl optimizes vector<bool> by using
          _Bit_reference instead of bool to conserve space. */
        int f = 0;
        cerr << '{';
        for (auto &&i : v)
            cerr << (f++ ? "," : "") << (i ? "T" : "F");
        cerr << "}";
    }
    /* Templates Declarations to support nested datatypes */
    template <typename T>
    void print(T &&x);
    template <typename T>
    void print(vector<vector<T>> mat);
    template <typename T, size_t N, size_t M>
    void print(T (&mat)[N][M]);
    template <typename F, typename S>
    void print(pair<F, S> x);
    template <typename T, size_t N>
    struct Tuple;
    template <typename T>
    struct Tuple<T, 1>;
    template <typename... Args>
    void print(tuple<Args...> t);
    template <typename... T>
    void print(priority_queue<T...> pq);
    template <typename T>
    void print(stack<T> st);
    template <typename T>
    void print(queue<T> q);
    /* Template Datatypes Definitions */
    template <typename T>
    void print(T &&x)
    {
        /*  This works for every container that supports range-based loop
            i.e. vector, set, map, oset, omap, dequeue */
        int f = 0;
        cerr << '{';
        for (auto &&i : x)
            cerr << (f++ ? "," : ""), print(i);
        cerr << "}";
    }
    template <typename T>
    void print(vector<vector<T>> mat)
    {
        int f = 0;
        cerr << "\n~~~~~\n";
        for (auto &&i : mat)
        {
            cerr << setw(2) << left << f++, print(i), cerr << "\n";
        }
        cerr << "~~~~~\n";
    }
    template <typename T, size_t N, size_t M>
    void print(T (&mat)[N][M])
    {
        int f = 0;
        cerr << "\n~~~~~\n";
        for (auto &&i : mat)
        {
            cerr << setw(2) << left << f++, print(i), cerr << "\n";
        }
        cerr << "~~~~~\n";
    }
    template <typename F, typename S>
    void print(pair<F, S> x)
    {
        cerr << '(';
        print(x.first);
        cerr << ',';
        print(x.second);
        cerr << ')';
    }
    template <typename T, size_t N>
    struct Tuple
    {
        static void printTuple(T t)
        {
            Tuple<T, N - 1>::printTuple(t);
            cerr << ",", print(get<N - 1>(t));
        }
    };
    template <typename T>
    struct Tuple<T, 1>
    {
        static void printTuple(T t) { print(get<0>(t)); }
    };
    template <typename... Args>
    void print(tuple<Args...> t)
    {
        cerr << "(";
        Tuple<decltype(t), sizeof...(Args)>::printTuple(t);
        cerr << ")";
    }
    template <typename... T>
    void print(priority_queue<T...> pq)
    {
        int f = 0;
        cerr << '{';
        while (!pq.empty())
            cerr << (f++ ? "," : ""), print(pq.top()), pq.pop();
        cerr << "}";
    }
    template <typename T>
    void print(stack<T> st)
    {
        int f = 0;
        cerr << '{';
        while (!st.empty())
            cerr << (f++ ? "," : ""), print(st.top()), st.pop();
        cerr << "}";
    }
    template <typename T>
    void print(queue<T> q)
    {
        int f = 0;
        cerr << '{';
        while (!q.empty())
            cerr << (f++ ? "," : ""), print(q.front()), q.pop();
        cerr << "}";
    }
    /* Printer functions */
    void printer(const char *) {} /* Base Recursive */
    template <typename T, typename... V>
    void printer(const char *names, T &&head, V &&...tail)
    {
        /* Using && to capture both lvalues and rvalues */
        int i = 0;
        for (size_t bracket = 0; names[i] != '\0' and (names[i] != ',' or bracket != 0); i++)
            if (names[i] == '(' or names[i] == '<' or names[i] == '{')
                bracket++;
            else if (names[i] == ')' or names[i] == '>' or names[i] == '}')
                bracket--;
        cerr << varName;
        cerr.write(names, i) << outer << " = " << varValue;
        print(head);
        if (sizeof...(tail))
            cerr << outer << " ||", printer(names + i + 1, tail...);
        else
            cerr << outer << "]\n"
                 << white;
    }
    /* PrinterArr */
    void printerArr(const char *) {} /* Base Recursive */
    template <typename T, typename... V>
    void printerArr(const char *names, T arr[], size_t N, V... tail)
    {
        size_t ind = 0;
        cerr << varName;
        for (; names[ind] and names[ind] != ','; ind++)
            cerr << names[ind];
        for (ind++; names[ind] and names[ind] != ','; ind++)
            ;
        cerr << outer << " = " << varValue << "{";
        for (size_t i = 0; i < N; i++)
            cerr << (i ? "," : ""), print(arr[i]);
        cerr << "}";
        if (sizeof...(tail))
            cerr << outer << " ||", printerArr(names + ind + 1, tail...);
        else
            cerr << outer << "]\n"
                 << white;
    }
}
#ifndef ONLINE_JUDGE
#define debug(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
#define debugArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#define debugArr(...)
#endif
#endif

#define int long long int

int mod = 998244353;

void query(vector<int>&d, int index, map<int, int>& cnt, int num, int num_cnt, int& sum) {
    if (index >= d.size()) {
        if (num_cnt <= 0 || cnt.find(num) == cnt.end()) return;
        else if (num_cnt & 1) sum += cnt[num];
        else sum -= cnt[num];
        sum = (sum + mod) % mod;
    } else {
        query(d, index + 1, cnt, num, num_cnt, sum);
        query(d, index + 1, cnt, num * d[index], num_cnt + 1, sum);
    }
}

void update(vector<int>&d, int index, map<int, int>& cnt, int num, int num_cnt, int sum) {
    if (index >= d.size()) {
        if (num_cnt <= 0) return;
        cnt[num] += sum;
        cnt[num] %= mod;
    } else {
        update(d, index + 1, cnt, num, num_cnt, sum);
        update(d, index + 1, cnt, num * d[index], num_cnt + 1, sum);
    }
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans = 0;
    map<int, int> cnt; // num -> {cnt}
    for (int i = 0; i < n; i++) {
        int x = a[i];
        vector<int> d;
        for (int j = 2; j*j <= x; j++) {
            if (x % j == 0) {
                while (x % j == 0) x /= j;
                d.push_back(j);
            }
        }
        if (x > 1) d.push_back(x);
        int sum = 0;
        query(d, 0, cnt, 1, 0, sum);
        if (i <= 0) sum = 1;
        update(d, 0, cnt, 1, 0, sum);
        debug(d, cnt, sum);
        ans = sum;
    }
    cout << ans << endl;
    debug(ans);
}

/*

Solve more simple version in the case where the graph is already given. Unfortunately, the answer to this question is not
obvious to me. Obvious solutions like BFS and then have subtrees add or something of that nature do not work. Not really obvious
but just an initial guess. 

primes:
2: 1 1 0 1 1
3: 0 1 1 0 1

2: 1 2 2
3: 0 2 2

Observation: Graph is acyclic
=> When acyclic, DP can easily solve number of paths

Algo: Store number of paths via each prime factor and sum previous one

==> pattern is like: 1 1 2 4 8
Add across different prime factors and set them both equal to that value.

[x, y] = [old cnt, new cnt];
initialized to [0, 1]
add factor
    => [x', y'] = [x + y, x + y]
check
    => [0, 1] => [1, 1] => [2, 2] => [4, 4]

primes: (first example)
2: 0, 1 => 1, 1 => 2, 2 => 4, 4
3: 0, 1 => 1, 1 => 2, 2

Algorithm currently failing as it's adding it up to 6 instead of 5. Here is the counterexample:
5
2 6 3 4 6
It has 4 numbers with prime factor of 2 while 3 numbers with prime factor of 3. So the prime factor of 2 is contributing 4 so
that means the 3 should contribute 2 but it only contributes 1. Ah ok, the issue is that the prime factor of 3 and 2 are double
counted for each.

Idea is to use inclusion-exclusion to keep track of things. This works because 2^n where n is the number of primes in one
number is quite small - about at most 20 numbers. Therefore, can keep track of repeats for each pair of prime factors 
which will be unique as a multiplication. The idea is that the subset of of prime factors for a particular combination
will result in the number of repeats which is the total number of nodes that both factors pass through. 
=> 2 factors will have solutions for {a}, {b}, and {a, b}. 
=> 3 factors will have solutions for {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}

Easy algo exists for O(n^2) time complexity as you would just need to count prefix of numbers. The problem boils
down to a subproblem which solves it completely which is find number of paths in acyclic graph. Finding numbers
with non zero gcd takes linear time and adding takes linear time in the DP so then we do this for every number
to get a quadratic solution. Most obvious simplification is to have store it via prime factors but then
the numbers would end of repeating when prime factors are shared.

Solution using inclusion-exclusion for prime factors solution will take O(n * 2^20) as a rough approximation which is 
still way too slow and even slower than the previous solution. Nevermind, this failed to realize that the primes
are unique and makes a huge difference when so as the product of the first ten primes is > 10^9 which is insane. 
I guess roughly double it would have doubling powers of 2 so in some ways it makes sense
=> I was looking 10! instead of primes which would grow up to close to 30
=> Here is OEIS link: https://oeis.org/A002110
Therefore, true running time would be closer to O(n * 2^)

6.67 * 10^9 / (23*29) => Going to be roughly 2^8 different states or each iteration in n.
=> 2^8 * 2* 10^5 = 51200000 => roughly 5 * 10^7

Optimized Algo: Go through each possible combination of unique primes and add them together.
=> The idea is to find number of paths that go through each prime factor. So 2 and 3 would
be problematic because previous paths which contain 2 and 3 := z (total paths) would
be set to both 2 and 3. But since it will be counted both times, then z should be subtracted
for 6.

How does this generalize to 3 factors?: 
Suppose we find number of paths that go through 2, 3, 5. Then our answer for number of paths is
x + y + z. The next query for 2, 3, 5 will be 2(x+y+z) while the sum is 6(x+y+z). 

x+y+z + x+y for a query for {2, 3} which can we calculated by summing up {2, 3} and subtracting z.

=> Generalizes to 4 factors: x+y+z+w for all. Then it would be 2(x+y+z+w) - (z+w) - (z+w). 
Value mapped to 6 ({2, 3}) would need to contain 2(z+w) = cnt_{2, 3} * left where cnt is cardinality
of set while left is the leftover sum. 
=> cnt{subset selected} * remaining sum

Does this generalize across multiple nodes?
=> 3 factors initially so it has x+y+z across all 3. Then we can add the same node element to get
3*(x+y+z) 

Problem with this method is that it is extremely hard to reason about or think for that matter. 

query for {2, 3, 5}:
x+y+z => sum for each prime factor
x+y+z + x+y for {2, 3} => need to subtract z
x+y+z + x for {2} => need to subtract y+z
x+y+z + y for {3} => need to subtract x+z

Figured out method while I was at gym. The idea is to have to functions, one to query and then one to update for all possible
selections of prime factors. The query will use inclusion exclusion by subtracting out the even cardinality subsets 
and add in the odd cardinality subsets. The update will add to all the possible subsets and sets. 

Query part:
Need all the sets information including the set itself and the intersection between itself and everything else.

Update or query:

Is the first step to query or to update the selection. The idea is to mirror what the O(n^2) dp is doing so the first step
is to query for the number of paths that go through the current node and then update what it will be for the next node
using that value. Base case is suppose we have a single node containing some subset of prime factors. Since there are no backedges
to any previous nodes, the base case here instead of being 0 is 1 path. Then all the prime factors should be updated with that 
value which should be 1. Then let us induct on this so suppose we have another node after. Querying the number of paths
that goes through it supposing the value of the node is the same as the start node, then the answer would be 1. Then the update
should add 1 everywhere such that the next query will provide 2 which is correct for the number of paths to get to that node
and so forth and so on. 

*/ 