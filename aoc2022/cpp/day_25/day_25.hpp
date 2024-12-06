#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class FullOfHotAir {
public:
    FullOfHotAir(string filename) {
        ReadSNAFUFromFile(filename);
    }
    string GetCountFull() {
        string snafuStr;
        long long fullCount = 0;
        for (auto snafu : snafuDigits) {
            long long full = ConvertSnafuToDigits(snafu);
            fullCount += full;
        }
        string reverseSnafuStr;
        while (fullCount > 0) {
            long long rem = fullCount % 5;
            switch (fullCount % 5) {
            case 4:
                reverseSnafuStr += '-';
                fullCount += 1;
                break;
            case 3:
                reverseSnafuStr += '=';
                fullCount += 2;
                break;
            default:
                reverseSnafuStr += (char)('0' + rem);
                fullCount -= fullCount % 5;
                break;
            }
            fullCount /= 5;
        }
        snafuStr.resize(reverseSnafuStr.size());
        for (int i = reverseSnafuStr.size() - 1; i >= 0; i--) {
            snafuStr[reverseSnafuStr.size() - 1 - i] = reverseSnafuStr[i];
        }
        return snafuStr;
    }
private:
    vector<string> snafuDigits;
    void ReadSNAFUFromFile(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            if (!line.empty()) {
                snafuDigits.push_back(line);
            }
        }

        inputFile.close();
    }
    long long ConvertSnafuToDigits(string snafu) {
        long long convert = 0;
        long long osn = 1;
        long long digitCount = 0;
        for (int i = snafu.size() - 1; i >= 0; i--) {
            long long val = 0;
            switch (snafu[i]) {
            case '-':
                val = -1;
                break;
            case '=':
                val = -2;
                break;
            case '0':
            case '1':
            case '2':
                val = snafu[i] - '0';
                break;
            }
            convert += val * osn;
            osn *= 5;
            digitCount++;
        }
        return convert;
    }
};

void day25_start(string filename) {
    cout << endl << "Day 25" << endl;
    FullOfHotAir fullOfHotAir(filename);
    cout << "part1: " << fullOfHotAir.GetCountFull() << endl;
}