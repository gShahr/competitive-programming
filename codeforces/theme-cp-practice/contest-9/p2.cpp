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
        int med = (n+1)/2;
        if ((k == 1 || k == n) && n != 1) cout << -1 << endl;
        else {
            vector<int> ans = {1, k, k+1};
            if (n == 1) ans = {1};
            else if (k&1) ans = {1, k-1, k+2};
            debug(ans);
            cout << ans.size() << endl;
            for (int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';
            cout << endl;
        }
    }
}

/*
https://codeforces.com/problemset/problem/2032/B

Any n => can split into (n+1)/2 to get that median which is nice.

n = 15, k = ?
m = 3
1, 2, 3, 4, 5
6, 7, 8, 9, 10
11, 12, 13, 14, 15
=> [3, 8, 13] => 8

1 2 4 5 6
3 7 8 9 10
11 12 13 14 15
=> [4, 8, 13] => 8

1 2 4 5 8
3 6 7 9 10
11 12 13 14 15
=> [4, 7, 13] => 7

Can generate [6, 7, 8, 9, 10]

1, 2, 6, 7, 8
3, 4, 5, 9, 10
11, 12, 13, 14, 15
=> [5, 6, 13] => 6

1, 2, 3, 4, 5
6, 7, 9, 10, 11
8, 12, 13, 14, 15
=> [3, 9, 13] => 9

1, 2, 3, 4, 5
6, 7, 8, 9, 10
11, 12, 13, 14, 15
=> [3, 8, 13] => 8

1, 2, 3, 4, 11
12, 13, 8, 9, 10
5, 6, 7, 14, 15
=> [3, 7, 10] => 7

1, 2, 3, 4, 5
6, 7, 8, 9, 10
11, 12, 13, 14, 15
=> [3, 8, 13] => 8

1, 2, 3, 4, 5
6, 7, 11, 12, 13
8, 9, 10, 14, 15
=> [3, 9, 13] => 9

Problem with trying to get 5 is that the old median is ripped out making it larger and basically subsituting the 5 in for the position
the 3 was taking in the final median.

Valid range is [d * n/2d + 1, d * n/2d + d]

1 4 11 => [6]
1 5 11 => [7]
1 6 11 => [8]
1 6 8 => [9, 10]

1, 2, 3, 4, 5
, , 6, 9, 10
11, 12, 13, 14, 15
=> [3, 8, 13] => 8

If going downwards from x to some x-d, decrease middle element by x-d.
So it's standard answer, ans[d/2] -= ((n+1)/2 - k).
Otherwise, it goes up so set ans[d/2+1] = ans[d/2].

n = 9, k = 6

1 2 5
3 4 6
7 8 9

If I have a number like 9, what other things can I get from it besides 4, 5, 6?

Something like 21, then

m1 = 6 => 1 2 6 
m2 = 7 => 3 4 7
m3 = 9 => 5 8 9

We don't care about the numbers larger than this since we don't have to provide them so we should just focus on the smallest elements
possibl and construct from that.

m1 = 1 2 4 6 7
m2 = 3 4 11
m3 = 5 6 12

n = 15, k = ?
1, 2, 3, 4, 5
6, 7, 8, 9, 10
11, 12, 13, 14, 15

1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
=> 
m1 = 3
m2 = 8
m3 = 13
=> {1, 6, 11}

1 2 3 11 12
4 7 8 10 13
5 6 9 14 15
=> median = 8

1 2 3 11 12
4 8 9 10 13
6 5 7 14 15
=> median = 9

Why doesn't something like 2:13 

*/

/*

n = 25, k = 17
range = (9, 17)

1 2 3 4 5
6 7 8 9 10
11 12 17 21 22
13 14 18 19 20
15 16 23 24 25

3
3
2
1+8, 25-8
=> x = (d/2) * (n/(2*d) + 1) + n/(2*d)
=> range = [1+x, n-x]

test: 15
=> x = 2 * 2 + 1
=> range = [6, 10]

1, 2, 3, 4, 5
6, 7, 10, 11, 12
8, 9, 13, 14, 15

=> +d, +n/2d

1 2 3 4 5
6 10 11 12 13
7 8 9 14 15
16 17 18 19 20
21 22 23 24 25

Nice. Ok I misread the problem you are given a permutation from 1 to n in order and supposed to split that up into strictly subarrays. Wait,
there median can only be (n+1)/2 in this case because you have to keep it in order which means you can always make it just be 1. Oh my fucking
god, I thought m had to divide n but it doesn't have to!

Ok so two things I got wrong about this problem. 1 that we can choose any initial ordering for the array and then split it up into
subarrays. 2 that m had to divide n. Glad to know I am an expert at not fully understanding problem statements.

So any number should be possible except for the ends at 1 and n. Otherwise, we can always split it up into 3 groups where group 1
is 1, group 3 is n, and group 2 is everything else. Otherwise, everything else should be possible because we can go from 2 to n-1.

Algo: Just put all the numbers from 1 to k-1 in group 1. k by itself in group 2 and k+1 to n in group 3.
*/