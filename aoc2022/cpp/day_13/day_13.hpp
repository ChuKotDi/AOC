#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <limits>

using namespace std;

const string PACK2_STR = "[[2]]";
const string PACK6_STR = "[[6]]";

class strangeLine {
    public:
        strangeLine(string str) {
            this->line = str;
            this->generateStrangeCode();
        }
        vector<int> getStrangeCode() {
            return this->strangeCode;
        };
        strangeLine& operator= (const strangeLine& strange) {
            this->line = strange.line;
            this->strangeCode = strange.strangeCode;

            return *this;
        }
        bool stringEqualCompare(const string& str) {
            return this->line == str;
        }
    private:
        const int BRACE_POWER = 100;
        const int TEN_POWER = 10;
        string line;
        vector<int> strangeCode;
        void generateStrangeCode() {
            string line = this->line;
            vector <int> code;
            int brace_power = 0;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == '[' && line[i + 1] == ']') {
                    code.push_back(0);
                    i++;
                }
                else if (line[i] == ']') {
                    brace_power -= BRACE_POWER;
                }
                else if (line[i] == ',') {
                    code.push_back(brace_power);
                }
                else if (line[i] >= '0' && line[i] <= '9') {
                    int numberCode = (int)line[i];
                    if (line[i + 1] >= '0' && line[i + 1] <= '9') {
                        numberCode += (int)line[i + 1] + TEN_POWER;
                        i++;
                    }
                    code.push_back(numberCode);
                }
                else if (line[i] == '[') {
                    brace_power += BRACE_POWER;
                }
            }
            code.push_back(INT_MIN);
            this->strangeCode = code;
        }
};

int compareStrangeLines(strangeLine* strangeLine1, strangeLine* strangeLine2) {
    int result = 0;
    vector<int> code1 = strangeLine1->getStrangeCode();
    vector<int> code2 = strangeLine2->getStrangeCode();
    int size = code1.size() > code2.size() ? code1.size() : code2.size();
    for (int i = 0; i < size; i++) {
        if (code1[i] != code2[i]) {
            result = code1[i] < code2[i] ? -1 : 1;
            break;
        }
    }
    return result;
}

void sortLines(vector<strangeLine>* strangeLines) {
    vector<strangeLine> lines = (*strangeLines);
    for (int i = 0; i < lines.size(); i++) {
        strangeLine line = lines[i];
        int ind = i;
        for (int j = i + 1; j < lines.size(); j++) {
            strangeLine line2 = lines[j];
            int res = compareStrangeLines(&line2, &line);
            if (res == -1) {
                line = line2;
                ind = j;
            }
        }
        strangeLine tmp = lines[i];
        lines[i] = line;
        lines[ind] = tmp;
    }
    (*strangeLines) = lines;
}

void day13_start(string filename) {
    cout << endl << "Day 13" << endl;
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл потерялся оО" << endl;
        return;
    }

    int part1{ 0 }, part2{ -1 };
    int index = 1;
    vector<strangeLine> lines;
    while (!inputFile.eof()) {
        string line1;
        getline(inputFile, line1);

        if (!line1.empty()) {
            string line2;
            getline(inputFile, line2);
            strangeLine strange1(line1);
            strangeLine strange2(line2);
            int res = compareStrangeLines(&strange1, &strange2);
            if (res < 0) {
                part1 += index;
            }
            index++;
            lines.push_back(strange1);
            lines.push_back(strange2);
        }
    }
    cout << endl;
    strangeLine strangePack2(PACK2_STR);
    lines.push_back(strangePack2);
    strangeLine strangePack6(PACK6_STR);
    lines.push_back(strangePack6);
    sortLines(&lines);
    int pack2 = 0, pack6 = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].stringEqualCompare(PACK2_STR)) {
            pack2 = i + 1;
        }
        if (lines[i].stringEqualCompare(PACK6_STR)) {
            pack6 = i + 1;
        }
    }
    part2 = pack2 * pack6;

    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
