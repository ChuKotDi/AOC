#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>

using namespace std;

void day3_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
    }

    int part1{ 0 }, part2{ 0 };
    string duplicates;
    vector<string> input;
    while (!inputFile.eof()) {
        string badge;
        getline(inputFile, badge);
        input.push_back(badge);
        bool work = true;
        for (int i = 0; i < badge.size() / 2 && work; i++) {
            for (int j = badge.size() / 2; j < badge.size() && work; j++) {
                if (badge[i] == badge[j]) {
                    part1 += isupper(badge[i]) ? badge[i] - '&' : badge[i] - '`';
                    work = false;
                }
            }
        }
    }

    for (int i = 0; i + 2 < input.size(); i += 3) {
        bool work = true;
        for (int m = 0; m < input[i + 0].size() && work; m++) {
            for (int j = 0; j < input[i + 1].size() && work; j++) {
                if (input[i + 0][m] == input[i + 1][j]) {
                    for (int k = 0; k < input[i + 2].size() && work; k++) {
                        if (input[i + 0][m] == input[i + 2][k]) {
                            part2 += isupper(input[i + 0][m]) ? input[i + 0][m] - '&' : input[i + 0][m] - '`';
                            work = false;
                        }
                    }
                }
            }
        }
    }

    cout << endl << "Day 3" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
