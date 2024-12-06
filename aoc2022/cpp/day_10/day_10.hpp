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

using namespace std;

char getPixel(int x, int cycleNumber) {
    int pixelPosition = cycleNumber % 40;

    if (pixelPosition >= x && pixelPosition <= x + 2 || pixelPosition == 0 && x >= 38) {
        return '#';
    }
    return '.';
}
void day10_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
        return;
    }

    int part1{ -1 };
    int x = 1;
    vector<int> cycles;
    cycles.push_back(x);
    while (!inputFile.eof()) {
        comandLine line;
        string s;
        int num = 0;
        inputFile >> s;
        if (!s.empty()) {
            if (s == "noop") {
                cycles.push_back(x);
            }
            if (s == "addx") {
                inputFile >> num;
                cycles.push_back(x);
                cycles.push_back(x);
                x += num;
            }
        }
        else {
            break;
        }
    }

    part1 = 0;
    for (int i = 20; i < cycles.size(); i += 40) {
        part1 += i * cycles[i];
    }

    cout << endl << "Day 10" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << endl;
    for (int i = 1; i < cycles.size(); i++) {
        cout << getPixel(cycles[i], i);
        if (i % 40 == 0) {
            cout << endl;
        }
    }
    inputFile.close();
}
