#include <bits/stdc++.h>

using namespace std;



/*
 * Complete the 'calculateContentStrength' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts STRING clip as parameter.
 */

long calculateContentStrength(string clip) {

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string clip;
    getline(cin, clip);

    long result = calculateContentStrength(clip);

    fout << result << "\n";

    fout.close();

    return 0;
}
