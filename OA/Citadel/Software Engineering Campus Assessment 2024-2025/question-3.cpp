#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'getRecommendedFriends' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY friendships
 */
 
void dfs(int x, int depth, set<bool>& visited, vector<vector<int>>& adj, map<int, int>& cnt) {
    if (visited.find(x) != visited.end()) return;
    visited.insert(x);
    if (depth >= 2) {
        cnt[x]++;
    } else {
        for (auto u: adj[x]) {
            dfs(u, depth+1, visited, adj, cnt);
        }
    }
}

vector<int> getRecommendedFriends(int n, vector<vector<int>> friendships) {
    vector<vector<int>> adj(n);
    for (auto v: friendships) {
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back((v[0]));
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        set<bool> visited;
        map<int, int> cnt;
        dfs(i, 0, visited, adj, cnt);
        int mx_ind = -1;
        int mx_value = -1;
        for (auto j: cnt) {
            if (j.second > mx_value) {
                mx_value = j.second;
                mx_ind = j.first;
            }
        }
        ans.push_back(mx_ind);
    }
    return ans;
}

/*

Brute force dfs at depth less than or equal to 2

*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string friendships_rows_temp;
    getline(cin, friendships_rows_temp);

    int friendships_rows = stoi(ltrim(rtrim(friendships_rows_temp)));

    string friendships_columns_temp;
    getline(cin, friendships_columns_temp);

    int friendships_columns = stoi(ltrim(rtrim(friendships_columns_temp)));

    vector<vector<int>> friendships(friendships_rows);

    for (int i = 0; i < friendships_rows; i++) {
        friendships[i].resize(friendships_columns);

        string friendships_row_temp_temp;
        getline(cin, friendships_row_temp_temp);

        vector<string> friendships_row_temp = split(rtrim(friendships_row_temp_temp));

        for (int j = 0; j < friendships_columns; j++) {
            int friendships_row_item = stoi(friendships_row_temp[j]);

            friendships[i][j] = friendships_row_item;
        }
    }

    vector<int> result = getRecommendedFriends(n, friendships);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
