#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMinMachines' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY start
 *  2. INTEGER_ARRAY end
 */

int getMinMachines(vector<int> start, vector<int> end) {
    multiset<pair<int, int>> remaining; // {end, start}
    int n = start.size();
    for (int i = 0; i < n; i++) {
        remaining.insert({end[i], start[i]});
    }
    int ans = 0;
    while (!remaining.empty()) {
        auto it = remaining.begin();
        pair<int, int> curr = *it;
        auto next = it;
        next++;
        remaining.erase(it);
        while (next != remaining.end()) {
            pair<int, int> nextPair = *next;
            if (next != remaining.end() && nextPair.second <= curr.first) {
                next++;
                nextPair = *next;
                continue;
            }
            if (next == remaining.end()) break;
            cout << curr.first << ' ' << curr.second << endl;
            curr = *next;
            it = next;
            next++;
            remaining.erase(it);
        }
        ans++;
    }
    return ans;
}

/*

3 6 => 1
1 7
6 7
8 9 => 1
9 14

greedy scheduling problem with n-machines
variant to the standard problem where we want max subset that can be scheduled

*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string start_count_temp;
    getline(cin, start_count_temp);

    int start_count = stoi(ltrim(rtrim(start_count_temp)));

    vector<int> start(start_count);

    for (int i = 0; i < start_count; i++) {
        string start_item_temp;
        getline(cin, start_item_temp);

        int start_item = stoi(ltrim(rtrim(start_item_temp)));

        start[i] = start_item;
    }

    string end_count_temp;
    getline(cin, end_count_temp);

    int end_count = stoi(ltrim(rtrim(end_count_temp)));

    vector<int> end(end_count);

    for (int i = 0; i < end_count; i++) {
        string end_item_temp;
        getline(cin, end_item_temp);

        int end_item = stoi(ltrim(rtrim(end_item_temp)));

        end[i] = end_item;
    }

    int result = getMinMachines(start, end);

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
