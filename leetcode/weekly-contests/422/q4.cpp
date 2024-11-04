#include <string>
using namespace std;

class Solution {
public:
    int countBalancedPermutations(string num) {
        
    }
};

/*

s1.size = n/2
s2.size = n/2

123
=> {x, y}, {z}

Interchange two numbers which the same
Idea is to find all distinct sets with equal sum <=> distinct s1
distinct s1 => distinct s2

Find all unique pairings of x elements taken from n elements and make their sum equal to the remaining elements
=> Find all unique pairings of x elements taken from n elements and make their sum equal to the remaining elements for a given sum

x = 10
sum = 30
*/