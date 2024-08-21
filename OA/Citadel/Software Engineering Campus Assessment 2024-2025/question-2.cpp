#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'countStableSegments' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY capacity as parameter.
 */

int countStableSegments(vector<int> capacity) {
    int ans = 0;
    int n = capacity.size();
    vector<long long int> cum(n+1, 0);
    for (int i = 0; i < n; i++) cum[i+1] = cum[i] + capacity[i];
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(cum.begin(), cum.end(), cum[i+1] + capacity[i]);
        int j = distance(cum.begin(), it);
        // check left is equal to right
        // check sum of interior is equal to left
        if (j < n && j - i + 1 >= 3
        && capacity[i] == capacity[j]
        && cum[j] - cum[i+1] == capacity[i]) {
            ans++;
        }
    }
    return ans;
}

/*

Binary search on prefix array

*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string capacity_count_temp;
    getline(cin, capacity_count_temp);

    int capacity_count = stoi(ltrim(rtrim(capacity_count_temp)));

    vector<int> capacity(capacity_count);

    for (int i = 0; i < capacity_count; i++) {
        string capacity_item_temp;
        getline(cin, capacity_item_temp);

        int capacity_item = stoi(ltrim(rtrim(capacity_item_temp)));

        capacity[i] = capacity_item;
    }

    int result = countStableSegments(capacity);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
