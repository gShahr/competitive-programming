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
        ans[x-1] = 0;
        ans[y-1] = 2;
        bool special1 = false;
        if (n % 2 == 0 && (y - x) % 2 == 0) special1 = true;
        else if (n % 2 == 0) ans[y-1] = -1;
        bool flip = !((x-1)&1);
        for (int i = 0; i < n; i++) {
            if (ans[i] == 2 && ! special1) continue;
            else if (ans[i] == -1 && flip) ans[i] = 0;
            else if (ans[i] == -1 && !flip) ans[i] = 1;
            flip ^= true;
        }
        debug(ans);
        for (auto x: ans) cout << x << ' ';
        cout << endl;
    }
}

/*

Hypothesis: Perhaps combining equations to deduce one of the values and then filling everything else in from there but it is not
obvious to me how to compute the required steps in order to solve it this way are.

I guess maybe try to solve the problem without the extra friend included. In this case, each dragon is friends with exactly two other 
dragons. Take the case where n = 3. Then 
    a1 = mex(a3, a2)
    a2 = mex(a1, a3)
    a3 = mex(a2, a1)
Then this would mean that 
    a1 = mex(mex(a2, a1), a2)
    If a1 = 0, then
        0 = mex(mex(a2, 0), a2)
        If a2 = 0, then it wouldn't work.
        If a2 != 0, then mex(a2, 0) would be != 0 and a the mex with that value and a2 would be != 0, which in that case would work.
        So the only solution is a2 such that it is != 0.
    If a1 = 1, then
        1 = mex(mex(a2, 1), a2)
        If a2 = 0, then it would work.
        If a2 = 1, then it wouldn't work.
        If a2 = 2, then it would work.
        If a2 = 3, then it would work.
        So the only solution that doesn't work is when a1 == a2. Otherwise all other solutions work.
    If a1 = 2, then
        2 = mex(mex(a2, 2), a2)
        If a2 = 0, then it would work.
        If a2 = 1, then it would work.
        If a2 = 2, then it wouldn't work.
        If a2 = 3, then it wouldn't work.
        So the only solution that works is when a2 = 0 or when a2 = 1.
    a1 can never be strictly more than 2 because the mex of two values will only produce 0, 1, and 2. in the case where you have 3 values,
    it can go up to 3 but that is it and I am not even sure if we ever use 3 even. But these are the only values allowed in a so it
    restricts in heavily (solely because of how the mex operation functions).

0 => 1
  => 2
1 => 0
  => 2
2 => 0
2 => 1

Possible solutions:
=> 0 1 2
=> 0 2 1
=> 1 0 2
=> 1 2 0
=> 2 0 1
=> 2 1 0

How to generalize solution for 4 dragons?:
    a1 = mex(a4, a2)
    a2 = mex(a1, a3)
    a3 = mex(a2, a4)
    a4 = mex(a3, a1)
We can pick a value for a1 and then find the rest of the values accordingly. I guess since a1 can at most be 3 values, we could
just check all possibilities and then from there. Setting a1 = 0 yields:
    0 = mex(a4, a2)
    a2 = mex(0, a3)
    a3 = mex(a2, a4)
    a4 = mex(a3, 0)
Maybe we can just brute force 3 values and then get back our result for the first value and then just cycle through to see if it
works or not.

How to generalize for 7 dragons?:
    a1 = mex(a7, a2)
    a2 = mex(a1, a3)
    a3 = mex(a2, a4)
    a4 = mex(a3, a5)
    a5 = mex(a4, a6)
    a6 = mex(a5, a7)
    a7 = mex(a6, a1)
Guess the values for the first 3 things, so guess the value of a1, a2, and a7. Then we can verify a2 and force select a value for a3.
Then we can keep cascading until we get a result for each element in array a.

Actually it looks like just selecting a1 and a2 seems to be enough as that will force all the other values.

How to generalize for 7 dragons with an additional mutual friendship:
    a1 = mex(a7, a2)
    a2 = mex(a1, a3)
    a3 = mex(a2, a4, a5)
    a4 = mex(a3, a5)
    a5 = mex(a3, a4, a6)
    a6 = mex(a5, a7)
    a7 = mex(a6, a1)
Guess a1, a2 => gives us a7
=> gives us a3
=> problem arrives at a3 where we have the 4 variables, 2 of which are 2 and 2 of which are not known. It looks like we need one
additional guess to cover the dragon friend so that we are able to fill it in. We would know their value from the friend and solve
them so the friend who also had 3 values will one have one free variable which we can deduce based on the previous answers for the
dragons.

Implementation: Involves some sort of DFS where I guess a1, a2, and x. If x is either a1 or a2, then I don't think it actually
matters to use another guess and it will suffice with just a1, a2. Since that value will be deduced and the friend will only have 
1 free variable whose value I need to deduce. Once a guess is made for 3 of the values, then I will need to check the validity of
each one and check if a solution possibly exists for it. I just need one solution so I can break out once I find one as it is
stated that the answer always exists. Once a1 and a2 are picked, I can solve for the rest of the values and see if it possible
or not. The LHS will be solved and the right hand side will have 1 or 2 values solved and one missing value. I need to deduce
what this value is based on the LHS. The problem right now is that the deduction can be multiple values. For instance, take a1
to be equal to 0 and a2 to be equal to 1. Then a3 can be any value greater or equal to 1. If I'm restricting values to be at most
3, then this is problematic because it can be 3 different values.

Then what is left for me to prove is that it is not good to have a3 be 1 or 3 but instead have it be 2. Intuitively, this feels
right but I am not able to prove it for this result.

1 0 1 0 2

0 1 2 0 1 2

example: 5 1 3
    a1 = mex(a5, a2, a3)
    a2 = mex(a1, a3)
    a3 = mex(a2, a4, a1)
    a4 = mex(a3, a5)
    a5 = mex(a4, a1)
    => 0 1 2 0 1
    => 2   2

0 1 2 1

Looking at test cases, we can always get an answer doing 0, 1, 2 and repeating this.
We can look at all cases of n and all cases of where the dragons friends are split apart.
Assume all is mod 3; Denote dragon friend as df
=> n = 0
    => df = 0
        => 0 1 2 0 2 1
        => ???
    => df = 1
        => Let df1 = 2 and df2 = 0 or vice versa in the period 0 1 2
        => Can also let df1 = 0 and df2 = 1 or vice versa
    => df = 2
        => Let df1 = 2 and df2 = 1 or vice versa in the period 0 1 2
=> n = 1
    => df = 0
    => df = 1
    => df = 2
=> n = 2
    => df = 0
    => df = 1
    => df = 2

7 3 6
=> 1 0 2 1 0 1 0
=> 0 1 2 0 1 0 1

=> Observation: We don't actually need the pattern 0 1 2, we just need 0, 1 for regular sequence and then with the additional
dragon friend, we can add a 2 and 1 to their position.

6 3 6
=> 1 0 0 ? 0 2

=> n is odd => 0 1 strategy works while making df1 = 0 and df2 = 2
=> n is even => make it odd by adding another 2 making df1 = 2 and df2 = 2 

Suppose that we have some sequence and there is a 0 placed somewhere and we need to fill it in such that the zeros and ones don't
touch each other. Then the distance between them needs always be 0 mod 2. So the place where we place the 0 or 1 needs to be the same.
Suppose that we place the 0, then if the distance or in this case i is even, then it's fine and we can use it. Otherwise, start at 1 
if the distance is odd.

=> n is even => make it odd by adding another 2 making df1 = 0 and df2 = 2 
=> 0 1 0 1 0 2

Only case left is when even n and even dist(x, y): 
? 0 ? 2
In this case we can assign df1 = 0 and df2 = 2. We can assign ones around the 2. Then we have 4 values filled in when n is even.
So we are left with an even amount of spaces left which lefts use the base case we observed before for even spaces.

1 2 1 ? ? ?

Same pattern can be applied by using 1 and 2 instead.

Simplification: df1 = 0 and df2 = 2 works for all. It just needs to be changed whether or not n is even or odd. If it's even,
it works fine but if it's odd, it needs to be modified to surround the 2 with ones.

0 1 2 1

1 0 1 2

even n
=> special case

0 ? 2 ? => 0 1 2 1
? 0 2 ? => 1 0 1 2

0 1 ? ? ? ? => special case 1: (odd distance away)
0 ? 2 ? ? ? => special case 2: (even distance away)

odd n
=> regular case works

? ? ? ? 2 => ? ? ? 1 2 => 0 1 0 1 2
? ? ? ? 2 => ? ? ? 0 2 => 1 0 1 0 2

regular case: set 0 and 2 state and then fill in with zeroes and ones
special case: surround the 2 with ones and then fill in with zeroes and ones

Actually for the regular case, no need to fill in the zero as {1, 2} or {0, 2} both work so we can fill in just the 2.
*/