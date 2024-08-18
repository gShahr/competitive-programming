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
class SegmentTree {
private:
    int n;
    std::vector<int> tree_max, tree_min, lazy;

    void build(const std::vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree_max[v] = arr[tl];
            tree_min[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree_max[v] = std::max(tree_max[v * 2], tree_max[v * 2 + 1]);
            tree_min[v] = std::min(tree_min[v * 2], tree_min[v * 2 + 1]);
        }
    }

    void push(int v) {
        if (lazy[v] != INT_MIN) {
            tree_max[v * 2] = lazy[v];
            tree_min[v * 2] = lazy[v];
            lazy[v * 2] = lazy[v];
            tree_max[v * 2 + 1] = lazy[v];
            tree_min[v * 2 + 1] = lazy[v];
            lazy[v * 2 + 1] = lazy[v];
            lazy[v] = INT_MIN;
        }
    }

    int query_max(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return INT_MIN;
        }
        if (l == tl && r == tr) {
            return tree_max[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return std::max(query_max(v * 2, tl, tm, l, std::min(r, tm)),
                        query_max(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }

    int query_min(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return INT_MAX;
        }
        if (l == tl && r == tr) {
            return tree_min[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return std::min(query_min(v * 2, tl, tm, l, std::min(r, tm)),
                        query_min(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }

    void update_range(int v, int tl, int tr, int l, int r, int new_val) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            tree_max[v] = new_val;
            tree_min[v] = new_val;
            lazy[v] = new_val;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update_range(v * 2, tl, tm, l, std::min(r, tm), new_val);
            update_range(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, new_val);
            tree_max[v] = std::max(tree_max[v * 2], tree_max[v * 2 + 1]);
            tree_min[v] = std::min(tree_min[v * 2], tree_min[v * 2 + 1]);
        }
    }

    int find_first_equal(int v, int tl, int tr, int l, int r, int x) {
        if (l > r) {
            return -1;
        }
        if (tl == tr) {
            return (tree_max[v] == x) ? tl : -1;
        }
        push(v);
        int tm = (tl + tr) / 2;
        if (tree_max[v * 2] >= x) {
            int res = find_first_equal(v * 2, tl, tm, l, std::min(r, tm), x);
            if (res != -1) return res;
        }
        return find_first_equal(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, x);
    }

    int find_last_equal(int v, int tl, int tr, int l, int r, int x) {
        if (l > r) {
            return -1;
        }
        if (tl == tr) {
            return (tree_max[v] == x) ? tl : -1;
        }
        push(v);
        int tm = (tl + tr) / 2;
        int res = find_last_equal(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, x);
        if (res != -1) return res;
        return find_last_equal(v * 2, tl, tm, l, std::min(r, tm), x);
    }

    void get_internal_array(int v, int tl, int tr, std::vector<int>& result) {
        push(v);
        if (tl == tr) {
            result[tl] = tree_max[v];
        } else {
            int tm = (tl + tr) / 2;
            get_internal_array(v * 2, tl, tm, result);
            get_internal_array(v * 2 + 1, tm + 1, tr, result);
        }
    }

public:
    SegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree_max.resize(n * 4);
        tree_min.resize(n * 4);
        lazy.resize(n * 4, INT_MIN);
        build(arr, 1, 0, n - 1);
    }

    int query_max(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }

    int query_min(int l, int r) {
        return query_min(1, 0, n - 1, l, r);
    }

    void update_range(int l, int r, int new_val) {
        update_range(1, 0, n - 1, l, r, new_val);
    }

    int find_first_equal(int l, int r, int x) {
        return find_first_equal(1, 0, n - 1, l, r, x);
    }

    int find_last_equal(int l, int r, int x) {
        return find_last_equal(1, 0, n - 1, l, r, x);
    }

    std::vector<int> get_internal_array() {
        std::vector<int> result(n, INT_MIN);
        get_internal_array(1, 0, n - 1, result);
        return result;
    }
};

int main() {
    int t;
    cin >> t;
    auto lambda = []() {
    };
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        SegmentTree aa(a);
        SegmentTree bb(b);
        vector<pair<int, int>> c;
        for (int i = 0; i < n; i++) {
            c.emplace_back(b[i], i);
        }
        sort(c.begin(), c.end());
        for (int i = 0; i < n; i++) {
            int z = i;
            i = c[i].second;
            if (a[i] != b[i]) {
                // int l = aa.find_first_equal(0, i, b[i]);
                // int r = aa.find_first_equal(i, n - 1, b[i]);
                // if (l != -1 && aa.query_max(l, i) == b[i] && bb.query_min(l, i) == b[i]) {
                //     aa.update_range(l, i, b[i]);
                // }
                // if (r != -1 && aa.query_max(i, r) == b[i] && bb.query_min(i, r) == b[i]) {
                //     aa.update_range(i, r, b[i]);
                // }
                int l = i;
                int r = i;
                while (r < n && a[r] != b[i]) {
                    if (b[i] > b[r] || a[r] > b[i]) r = n;
                    else r++;
                }
                while (l >= 0 && a[l] != b[i]) {
                    if (b[i] > b[l] || a[l] > b[i]) l = -1;
                    else l--;
                }
                if (r < n) {
                    aa.update_range(i, r, b[i]);
                    for (int j = i; j <= r; j++) {
                        a[j] = b[i];
                    }
                }
                if (l >= 0) {
                    aa.update_range(l, i, b[i]);
                    for (int j = l; j <= i; j++) {
                        a[j] = b[i];
                    }
                }
            }
            i = z;
        }
        a = aa.get_internal_array();
        bool ok = true;
        debug(a, b);
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

/*

get index k of b[i] in a in O(1) time
check b[i] > b[j] in segment for j != i in [i, k] <=> get max in segment
check a[j] < a[k] in segment for k != j in [i, k] <=> get max in segment

x   x   x   x+1
x+1 x   x   x

Go in increasing order from sequence B.
Higher values wipe out lower values as we move along the segment.
Can naively make a O(n^2) solution it fits within the time limits.

*/