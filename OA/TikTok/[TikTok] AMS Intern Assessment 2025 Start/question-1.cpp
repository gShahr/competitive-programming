#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'minDaysToTargetEngagement' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER initialEngagementScore
 *  2. LONG_INTEGER targetEngagementScore
 *  3. LONG_INTEGER_ARRAY trainingEngagementScore
 */

long minDaysToTargetEngagement(long initialEngagementScore, long targetEngagementScore, vector<long> trainingEngagementScore) {
    long days = 0;
    sort(trainingEngagementScore.begin(), trainingEngagementScore.end());
    long long int IES = initialEngagementScore;
    set<long long int> TES;
    for (auto i: trainingEngagementScore) TES.insert(i);
    while (IES < targetEngagementScore) {
        days++;
        auto it = upper_bound(TES.begin(), TES.end(), IES);
        long res = days;
        if (it != TES.begin()) {
            it--;
            if (res < *it) {
                res = *it;
                TES.erase(it);
            }
        }
        IES += res;
    }
    return days;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string initialEngagementScore_temp;
    getline(cin, initialEngagementScore_temp);

    long initialEngagementScore = stol(ltrim(rtrim(initialEngagementScore_temp)));

    string targetEngagementScore_temp;
    getline(cin, targetEngagementScore_temp);

    long targetEngagementScore = stol(ltrim(rtrim(targetEngagementScore_temp)));

    string trainingEngagementScore_count_temp;
    getline(cin, trainingEngagementScore_count_temp);

    int trainingEngagementScore_count = stoi(ltrim(rtrim(trainingEngagementScore_count_temp)));

    vector<long> trainingEngagementScore(trainingEngagementScore_count);

    for (int i = 0; i < trainingEngagementScore_count; i++) {
        string trainingEngagementScore_item_temp;
        getline(cin, trainingEngagementScore_item_temp);

        long trainingEngagementScore_item = stol(ltrim(rtrim(trainingEngagementScore_item_temp)));

        trainingEngagementScore[i] = trainingEngagementScore_item;
    }

    long result = minDaysToTargetEngagement(initialEngagementScore, targetEngagementScore, trainingEngagementScore);

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
