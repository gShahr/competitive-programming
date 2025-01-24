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
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> ans(n, -1);
        x--, y--;
        for (int i = y; i <= x; i++) ans[i] = 1;
        for (int i = y-2; i >= 0; i -= 2) ans[i] = 1;
        for (int i = x+2; i < n; i += 2) ans[i] = 1;
        debug(ans);
        for (auto i: ans) cout << i << ' ';
        cout << endl;
    }
}

/*
https://codeforces.com/problemset/problem/1990/B

Easy case is where x is strictly less than y, but that is excluded from here. My first thought is to fill the entire prefix up to x with
ones and then fill in the remaining suffix with a sum equal to or less than 0. The problem with this is that the suffix max will
always be 1 which is not always want we want so we have to change this slightly. 

Imagine we fill first x values with 1 and then the remaining values with -1. Then the prefix is satisifed but not the suffix as
it will be 1. So to move it up to the correct value we have to set the first y-1 values to -1 so that the suffix can be satisfid.
This is nice because it doesn't change the max value for prefix as the maximum and all subsequent maximums will be reduced by a 
constant amount - this being the negative values present here.

Since suffix takes the largest value here, then we just need to make the values past the suffix alternate between 0 and 1
so that the sum becomes 0 instead of some negative value which will start with -1 and become the maximum potentially. 

Ok, hard to think about two things at once as try to make the prefix work first and then the suffix. Makes the entire prefix
ones to satisfy it and then move onto the suffix. If we make the suffix all ones, then the suffix would work independently, but
both break when combining them so the first order of action would be trying to combine suffix with prefix so it doesn't break 
the prefix. Well to do that I can simply make the suffix -1 and it would work. Potential solutions for suffix with changing the prefix
from ones to negatives doesn't work because then it will be the new best suffix so we have to change the values in the suffix to
account for the fact that. Ok this line of thinking is getting me nowhere as I have to go back and forth for what I think is 
correct so the idea should be better presented.

Imagine we alternate with ones and negative ones in the array. Then x will be the end and y will be the beginning. 

-1 1 -1 1

Nevermind, the suffix is actually going to be the last element as well as the prefix. Ok so what if we wanted to shift
the prefix but not the suffix? Nevermind, the suffix in this is actually at 1 since it goes 1, 0, 1, 0. We can shift the 
suffix to the right by 1 by changing it to:

-1 -1 1 1

This maintains the prefix to be the last element and makes the suffix at 3 instead of 2. 

1 1 1 1 => x = 4, y = 1 
-1 1 -1 1 => x = 4, y = 2
-1 -1 1 1 => x = 4, y = 3
x = 4, y = 4 {not possible; hence why it is banned from constraints}

1 1 1 -1 => x = 3, y = 1
-1 1 1 -1 => x = 3, y = 2

1 1 1 1 1 => x = 5, y = 1
-1 1 1 1 1 => x = 5, y = 2
-1 -1 1 1 1 => x = 5, y = 3
-1 -1 -1 1 1 => x = 5, y = 4

1 1 1 1 -1 => x = 4, y = 1
-1 1 1 1 -1 => x = 4, y = 2
-1 -1 1 1 -1 => x = 4, y = 3

-1 1 1 -1 -1 => x = 3, y = 2

-1 -1 -1 1 1 1 => x = 6, y = 4

-1 1 -1 -1 1 1 => x = 6, y = 5

The pattern present here is to make all the values strictly past x negative 1 and the values strictly before y negative 1. 
Since x > y, then the interval [x, y] will always be at least size 2, which means that we will have double twos there. The problem
with the strategy outlined in the previous sentence is when we get something like x=6, y=5 where the negatives don't get superceded
by the positive values so it fails to overtake for the prefix but works for the suffix so if we could cancel that out somehow then
it would work. The idea is instead of negatives, to have alternating zeros and ones. We always want negatives ones on the outside
so that we are not increasing the suffix until negatives are applied and the same thing for the prefix. Acually this doesn't matter
as long as the previous value in the same direction is negative 1 so it negates the addition in the next step. From left to right,
this could look like negative followed by postiive. 


*/