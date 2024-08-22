vector<string> solution(vector<vector<string>> paragraphs, int width) {
    vector<string> result;
    string border(width + 2, '*');
    result.push_back(border);

    for (const auto& paragraph : paragraphs) {
        stringstream line;
        int currentWidth = 0;

        for (const auto& chunk : paragraph) {
            if (currentWidth + chunk.size() + (currentWidth > 0 ? 1 : 0) > width) {
                // Center align the current line
                string lineStr = line.str();
                int spacesToAdd = width - currentWidth;
                int leftSpaces = spacesToAdd / 2;
                int rightSpaces = spacesToAdd - leftSpaces;
                result.push_back("*" + string(leftSpaces, ' ') + lineStr + string(rightSpaces, ' ') + "*");

                // Start a new line
                line.str("");
                line.clear();
                currentWidth = 0;
            }

            if (currentWidth > 0) {
                line << " ";
                currentWidth++;
            }
            line << chunk;
            currentWidth += chunk.size();
        }

        // Add the last line of the paragraph
        if (currentWidth > 0) {
            string lineStr = line.str();
            int spacesToAdd = width - currentWidth;
            int leftSpaces = spacesToAdd / 2;
            int rightSpaces = spacesToAdd - leftSpaces;
            result.push_back("*" + string(leftSpaces, ' ') + lineStr + string(rightSpaces, ' ') + "*");
        }
    }

    result.push_back(border);
    return result;
}
