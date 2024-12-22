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
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        set<int> prices;
        for (int i = 0; i < n; i++) {
            prices.insert(a[i]);
            prices.insert(b[i]);
        }
        multiset<pair<int, int>> bucket1;
        multiset<int> bucket2;
        for (int i = 0; i < n; i++) {
            bucket1.insert({a[i], b[i]});
        }
        int ans = 0;
        for (int price: prices) {
            auto it = bucket1.begin();
            while (it != bucket1.end()) {
                if (price > it->first) {
                    if (price <= it->second) bucket2.insert(it->second);
                    it = bucket1.erase(it);
                } else break;
            }
            auto it2 = bucket2.begin();
            while (it2 != bucket2.end()) {
                if (price > *it2) it2 = bucket2.erase(it2);
                else break;
            }
            debug(price, bucket1, bucket2);
            int res = (bucket1.size() + bucket2.size()) * price;
            if (bucket2.size() <= k) ans = max(ans, res);
        }
        debug(ans);
        cout << ans << endl;
    }
}

/*

Really not sure about this problem. My first thought was to iterate each value of a, but then a problem arises with that and that doesn't guarantee a 
good value to use. So it seems like we can reduce search space down to only values consisting of a and b for the possible prices which ends up being
nice. The idea is really simple, if we make the initial assumption that there exists an optimal pice that isn't a or b, then that must mean
there exists a higher price which is either bounded by a or b. If it is bounded by a, then we can increase it freely without changing anything else
while still leaving a positive review. In the case if it is bounded by b, then we can freely increase price without changing anything else while
making that customer with the b leave a negative review. Note that this only affects one or more customers that is bounded on that area. But since 
we stop there, it only affects those customres with values at that location which don't affect their reviews or their purchase. All other customers
would have the same purchase and review but the price would be increased for them. For these customers, their purchase still stays the same and their
review stays the same, completing the proof.

Now the solution has boiled down to being O(n^2) but it needs to be faster. A simple idea that I'm not sure works is to go through the prices
in order which seems like a natural thing to do when computin this.

Key idea is that we can transition from each price state in increasing order because each element has at most 3 transitions outlined below:
    => buy tree and leave positive review
    => buy tree and leave negative review
    => don't buy tree
We somehow need to get the elements when they transition when a higher price is introduced. Suppose we start at price 0, then all the elements
are in the first state and we need to calculate the transition for price_i for i = 0. 

There are 3 possible transition states
    => 1 to 2 (price[i] > a[j] && price[i] <= b[j])
    => 1 to 3 (price[i] > b[j])
    => 2 to 3 (price[i] > b[j])
It seems that states 1 to 3 and 2 to 3 have the same condition so we can potentially combine them.

I can sort the values by a in order as that will be useful to either put it in bucket 2 or bucket 3 or keep it in bucket 1. I can get the index
of where price[i] > a[j] and have some right bounds that tells me where to stop. Once I know the elements I need, I can move them into
their respective buckets by comparing the values of b[j]. If price[i] > b[j], then I can just leave it to the side and don't do anything with it
as all the subsequent prices will be greater or equal so it will never be used again. For prices, that stay in bucket 1, I can just keep them
in the set.

For price[i] > b[j], I will delete it from the set and make the subsequent operations to modify the answer. For prices that maintain bucket 1,
leave them in there. For (price[i] > a[j] && price[i] < b[j]), need to make another bucket specifically with just values of b which denote
buying the tree but leaving negative reviews. Don't need to store third bucket as they don't leave a review or buy a tree. The answer will
be the size of both buckets multiplied by the price.

Then we need to check if anything changes for the second bucket by doing the same operation of having a right bounds of where we check
and taking the upperbound and deleting elements accordingly. 

Actually we don't even need to keep a right bounds as we can use a set instead of a vector to keep track of things as we don't every require
random access if we use pairs as we only care about each individual customer as each query will be independent. Bucket 2 size will
represent the amount of negative reviews.

Had to change from sets to multisets as we can get multiple people with the same price that we have to account for.

It's giving me time limit exceeded now so I need to adjust it and calculate how lon git's taking. We iterate through z=2n times
for each element as use it as a price range. We binary search on the ranges so each operation takes logz time. Each operation
can at most go to bucket 1 then bucket 2 and then to nowhere. So we only process each element at most two times. Therefore,
a rough estimate for time complexity is z(logz) + 2z = nlogn + 2n = 10^5(log10^5) + 2(10^5).

Example: {1, 4}, {2, 3}. Damn, I griefed this hard as the second bucket needs to be according to b values, not the a values
which it's sorted by. So it would potentially be out of order, and as a result would not work though I don't think this is the case
if it passed to test case 5. Assuming the logic is correct here, the issue is that it would iterate the entire thing resulting
in O(n^2) worst complexity which means that I would have to change this to work accordingly. The problem then is how does this
change for values that increase. 

{1, 4}, {2, 3}, {2, 2} => I don't see how it would be able to see which values to remove by saying that the price is 4. It should
remove the last two value but it will end up keeping it which is wrong in this scenario.

Now this is giving me wrong answer which is even more confusing as I don't understand how it's not supposed to go in the other
direction.

Ah damn it was overflow error that was getting it. Logic was correct but needed to change to long long int. Forgot that the answer
itself can be large because are multiplying the potential price with some number of elements. Rough estimate for max value is
10^5 * 10^9 = 10^14 which is max value for vector a or vector b along with max value for n for one test case.

*/