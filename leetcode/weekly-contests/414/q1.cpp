class Solution {
public:
    string convertDateToBinary(string inputDate) {
        return convertToBinary(inputDate);
    }

private:
    string convertToBinary(const string& inputDate) {
        istringstream dateStream(inputDate);
        string yearPart, monthPart, dayPart;
        getline(dateStream, yearPart, '-');
        getline(dateStream, monthPart, '-');
        getline(dateStream, dayPart, '-');
        string yearBinaryStr = bitset<32>(stoi(yearPart)).to_string().substr(bitset<32>(stoi(yearPart)).to_string().find('1'));
        string monthBinaryStr = bitset<32>(stoi(monthPart)).to_string().substr(bitset<32>(stoi(monthPart)).to_string().find('1'));
        string dayBinaryStr = bitset<32>(stoi(dayPart)).to_string().substr(bitset<32>(stoi(dayPart)).to_string().find('1'));
        return yearBinaryStr + "-" + monthBinaryStr + "-" + dayBinaryStr;
    }
};