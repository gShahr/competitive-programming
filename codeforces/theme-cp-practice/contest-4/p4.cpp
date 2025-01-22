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

// taken from https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/

int gcdExtended(int a, int b, int* x, int* y);

// Function to find modulo inverse of a
int modInverse(int A, int M) {
    int x, y;
    int g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else {
        int res = (x % M + M) % M;
        return res;
    }
}

// Function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int* x, int* y) {

    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }

    // To store results of recursive call
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

void count(string& s, char c, int modd, vector<int>& fact, pair<int, int>& ans, int& total) {
    int cnt = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) cnt++;
        else {
            if (cnt <= 0) continue;
            total += cnt-1;
            if (cnt > 1) ans.second = (ans.second * modInverse(fact[cnt-1], modd)) % modd;
            ans.first += cnt-1;
            ans.second *= fact[cnt];
            ans.second %= modd;
            cnt = 0;
        }
    }
    if (cnt <= 0) return;
    total += cnt-1;
    if (cnt > 1) ans.second = (ans.second * modInverse(fact[cnt-1], modd)) % modd;
    ans.first += cnt-1;
    ans.second *= fact[cnt];
    ans.second %= modd;
}

int32_t main() {
    int t;
    cin >> t;
    int modd = 998244353;
    vector<int> fact(2*1e5+1, 1);
    for (int i = 1; i <= 2*1e5; i++) fact[i] = (fact[i-1] * (i)) % modd;
    while (t--) {
        string s;
        cin >> s;
        pair<int, int> ans = {0, 1};
        int total = 0;
        count(s, '0', modd, fact, ans, total);
        count(s, '1', modd, fact, ans, total);
        ans.second = (ans.second * fact[total]) % modd;
        debug(ans);
        cout << ans.first << ' ' << ans.second << endl;
    }
}

/*
https://codeforces.com/problemset/problem/1879/C

If there is a segment of zeros or ones, those need to be removed for all except one of them. So SL (segment length) which we
can abbreviate as x, it will result in (x-1)! for the number of ways in which we can reomve x-1 elements. In the canonical
case, it would be x!. Whoops, in this case we can start by picking x elements then all the way down to x-2 elements left 
that we can pick so it's actually x! / 1!. Nevermind, was actually right since we only have 1 element left at the end
and there is only one way to pick 1 element so it doesn't affect our answer. 

So for instance, if we have 3 elements and we want to pick 2 of them, then we can select any of the 3 elements the first time
and then any of the 2 elements the second time so in total there would be x! or 6 ways to select the items since the last
element can only be chosen one way.

One special case is if the length of the segment is 1, then we should skip it as we do not want to remove it. The number
of total elements that we should sum up is going to be each segment minus 1 accumulated together.

Since we have two independent events happening and want to figure out the total number of ways that they can be selectd, we
should multiply them together. This can be inductively applied to x many different events so we should multiply all
of those together.

My logic here is wrong somehow for switching between ones and zeroes which is really annoying.

Need to understand this counter example. So it's 0101. So it increments the 0 counter by 1 and then goes to the 1
where it resets the flag to now expect ones instead. Ah ok, so the flag is being set to false but it's still 
expecting a zero here. The way I've implemented the solution is so fucking cancer and can't even debug it.
I've come up with a better way of implementing it but the flag thing is so weird.

Ah ok the flag being changed is just wrong. In the case where it's going from 1 -> 0, it's fine, but it runs
into the issue where if we go from 0 -> 1, then the flag needs to account for the fact that the ones now
need to be counted.

Not throwing a runtime error so I don't think the issue is with mod or anything to do logic wise. The initial
assumption is flat out wrong I think. In the case where we have something like 0011, the answer according
to my solution should be 4. 
=> {1, 2}, {1, 3}, {2, 2}, {2, 3}
Whoops, it needs to also include 4 more because I can do apply these operations in any order I want since
it needs to account for the fact that I can do the second operations first and then the first operations.

We can delete the extra 0 first or delete the extra 1 first or vice versa. 
For something where we have 000111, we have 3! for ways to pick ordering for first group and 3! for the number 
of ways to pick ordering for second group. If we do 3! * 3!, then for each ordering for the first group, we
append the second group. The problem with this is that we want something for like 6! to account for the fact
that we can mix opreations from the first and second group. Now the problem is that have blurred the lines
of trying to clear only 2 elements from each group which is why I like 3! better because it shows that we
have 3 elements to erease initially and then 2 and then we move onto the next group. To interlace these results,
it doesn't seem possible without fully comitting to something like 6!. It seems to be that if we take 6! / (3! * 3!)
then we get the answer but I am not able to prove. In the case where the answer was 8 for the example above,
we would get 24 and then divide by 4 to get 6 which is no the answer.

Relative positions
=> {1, 2}, {1, 3}, {2, 2}, {2, 3}
=> {3, 1}, {3, 2}, {4, 1}, {4, 2}

Absolute positions
=> {1, 3}, {1, 4}, {2, 3}, {2, 4}
=> {3, 1}, {3, 2}, {4, 1}, {4, 2}
=> 2! * 2! * 2 = 8

Yeah so figured it out while taking a nap - the idea is that we don't want to take factorials of the entire thing
because then it loses meaning - we want factorial of each individual group and then taking the number of ways
to select from that group and multiply them together. For insstance, for something like 00111, we have 2! ways
for the first group and 3! ways for the second group. There are 3!/(1! * 2!) ways to pick unique orderings 
of which elements we remove when selecting a group. It's strange because the way of going about it is
to pick some unique ordering and then appying all the ways to select from that group and the next
and so forth and so on. Actually, nevermind, in the case where one ordering is selected for us, the
number of choices will be 3! * 2! since if we choose the second group first which we eventually have to do,
we will have  3 choices at our disposable and the second time around, we will have 2 choices, becoming 6
unique choices. Therefore, to account for all the ways we can select the numbers, we should multiply by
the number of unique ways of selecting from each group.

As a result, the formula will be: some_segment_i! * sum(some_segment_i-1) / (some_segment_i-1)! for all i

Example: 00111

(2! * 3!) * (3! / (1! * 2!)) = 12 * 3 = 36

let k be the number of segments, then we end up with what we have below
(len_i)! * (n-k)! / (len_i-1)! = len_i * (n-k)! for all i which is what they end up with in the official editorial.

*/