vector<int> solution(string binaryString, vector<string> requests) {
    int n = binaryString.size();
    vector<int> zeroCount(n, 0);
    vector<int> answers;
    
    // Precompute the cumulative count of '0's
    zeroCount[0] = (binaryString[0] == '0') ? 1 : 0;
    for (int i = 1; i < n; ++i) {
        zeroCount[i] = zeroCount[i - 1] + (binaryString[i] == '0' ? 1 : 0);
    }
    
    bool flipped = false;
    
    for (const string& request : requests) {
        if (request.substr(0, 6) == "count:") {
            int index = stoi(request.substr(6));
            int count = zeroCount[index];
            if (flipped) {
                count = (index + 1) - count; // Total elements - count of '0's gives count of '1's
            }
            answers.push_back(count);
        } else if (request == "flip") {
            flipped = !flipped;
        }
    }
    
    return answers;

}
