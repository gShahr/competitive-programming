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

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, v;
        cin >> n >> m >> v;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> l, r; // inclusive points where boundary cuts are made
        // l = {0}; // include left boundary as a cut
        // r = {n-1}; // include right boundary as a cut
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            if (sum >= v) {
                l.push_back(i);
                sum = 0;
            }
        }
        sum = 0;
        for (int i = n-1; i >= 0; i--) {
            sum += a[i];
            if (sum >= v) {
                r.push_back(i);
                sum = 0;
            }
        }
        debug(l, r);
        vector<int> cum(n+1, 0);
        for (int i = 0; i < n; i++) cum[i+1] += cum[i] + a[i];
        int ans = -1;
        // consider all possible m cuts made
        for (int i = 1; i < m; i++) {
            int ll = i;
            int rr = m-i;
            ll--, rr--;
            debug(cum[l[ll]+1], cum[r[rr]], cum);
            if (ll >= l.size() || rr >= r.size()) continue;
            else if (l[ll] > r[rr]) continue;
            else ans = max(ans, cum[r[rr]] - cum[l[ll]+1]);
        }
        debug(ans);
        if (l.size() >= m) ans = max(ans, cum[n] - cum[l[m-1]+1]);
        if (r.size() >= m) ans = max(ans, cum[r[m-1]]);
        debug(ans);
        cout << ans << endl;
    }
}

/*

A boundary is determined if the left boundary is given and if the sum is minimized such that it is greater than the given v.

Suppose we need to just satisfy the second condition, in other words pick 1 boundary box such that each respective sum is greater
than or equal to v.
=> Given x1, x2, ..., xn 
=> Since we can only make one cut, then it has to be somewhere in the middle which means that we can find the answer in linear time
where we make the boundary cut where the prefix sum is first greater than or equal to v as to minimize the sum so that the sum to 
the right of boundary cut is maximized which means that any other potential cut taken will result in a value less than or equal to
the maximized value resulting in false if the maximized value is also false (strictly less than v).
=> the algo above can be generalized to multiple segments which all have to be greater or equal to v. But the 
question still remains how we can maximize the size of exactly one segment

Suppose we find the boundaries for m subarrays 

Suppose we need to satisfy the second condition with one sum while trying to maximize the other sum so the idea is to maximize one sum 
while making the other sum greater than or equal to v while being minimized.
=> Given x1, x2, ..., xn
=> 
=> Corollary: 

Theorem 1 => algo only needs one iteration starting from left going to the right.

v = 12, m = 1
10 10 1 1 1 1


What would Tourist do to solve this problem? Probably starts with trivial case where there are m+1 possible cuts that can be
made and realizes that we can brute force all possible n^(m+1) states. If we cache this via DP we can reduce running time
from exponential to O(nm) which is still too big. Therefore, some reduction via observation is needed here. He would
consider cuts we don't have to make it the array. In other words, cuts which are redundant or would make the answer worse.
Clearly if the sum of one segment becomes strictly smaller than v and that piece is going towards the m+1 subarrays, then
we should not consider it. m+1 subarrays is annoying to work with here because all the segments are uniform except one.

If the sum of one segment isn't at least v, then we should not consider it to go towards one of our m subarrays needed.
Better solution: Consider all possible pairs of elements from 1 to n and make them Alice's segment. Check if all other
segments form m subarrays such that their sum is greater than or equal to v. This algo can be computed in O(n^2).abort
Now tourist would be asking himself what other redundancies exist here as clearly there has to be some to make the algo
go from O(n^2) to either linear or O(nlogn). 

Alice would take some prefix and then segment m subarrays
Pick one subarray first and then alice picks some prefix 
<=> This algorithm is equivalent to the O(n^2) algorithm above.

Can't make transitions between the prefix and increasing it by one as you would be forced to shift all the subarrays to the 
right accordingly. Equivalent algo above is to consider {l, r} cuts where the last boundary box for l and first boundary for 
r determines ALice's segment. Then take the max across all possible pairs. Algorithm would similarly be O(n^2) as we would
have to consider all possible cuts. 

The algorithm abuses the fact that there is a O(1) transition between all possible states here. For example, consider making 
one cut from the right from the right boundary box, we could store all those boundary points beforehand and use prefix sums
to consider the sum between the boundary points. Making another cut form the right would have the left cut decrease by 1 and 
increase the right bound to the left. If r > l for all, then answer does not exist as we cannot make m subarrays with at least
v sum. However, if l <= r, then that means answer exists with at least one configuration. The answer is the max across these 
segments. 

Consider m subarrays:
Consider m+1 subarrays:
=> Not needed as it was solved above.

** Tourist thinking helped me solve this problem.abort

Struggling so much on the implementation for this problem unfortunately.
=> Consider the indices such that they form the boundary cuts. Then they are mapped to the indices in the cumulative array.
    The indices should then account for the sum between them. Normally when querying prefix arrays, we transform some
    (l, r) both inclusive to pre[r+1] - pre[l] where the pre is 0-indexed array. We need r+1 to account for the fact
    we want to include what is at pre[r]. In this case, we want to do the same but for (l+1, r-1) because the boundary
    cuts represent the last element in each segment that is included. Therefore, we can make a simple transformation
    using (l+1, r-1) => (x, y) => (x, y+1) => (l+1, r). 

    I'm trolling this. The formula is actually [l, r) where the right side is inclusive but the left side is left out.
    In the prefix, the sum on the leftmost one is cut out. Now subtracting both elements which are the same
    is not consistent.
=> Not working with subtracting both sides from each other. 

=> Now consider both edge case where l = m and r = 0 and where l = 0 and r = m. In the case where l = m and r = 0,
    then we want to query the m+1 where it is available. Since 0-indexed, query the mth element. Of course, check 
    bounds as well as we can't query something that does not exist. Then l[m-1]+1 goes all the way to the end so
    we want the sum of elements from (l[m-1]+1, n-1). 
    => Transform this to pre sum so (l[m-1]+1, n-1) => [l[m-1], n-1) => l[m-1], n


    In the other case, we want sum from (0, r[m-1]-1).
    => Transform this to pre sum so (0, r[m-1]-1) => [-1, r[m-1]) => -1, r[m-1]+1
    
    => The first one is available as the nth element exists within the prefix and the first element is bounded 
    between 0 and n-1 so it always exists in the prefix sum. The r[m-1] is also bounded in the prefix sum. The issue
    is with the -1 as it should be moved to the 0. Can consider -1 as nothing so can remove it from query.

*/