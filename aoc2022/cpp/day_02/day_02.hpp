#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>

using namespace std;

void day2_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
    }

    int part1{ 0 };
    int part2{ 0 };
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        switch (line[0]) {
            case 'A':
                switch (line[2]) {
                    case 'X':
                        part1 += 4;
                        part2 += 3;
                        break;
                    case 'Y':
                        part1 += 8;
                        part2 += 4;
                        break;
                    case 'Z':
                        part1 += 3;
                        part2 += 8;
                        break;
                }
                break;
            case 'B':
                switch (line[2]) {
                case 'X':
                    part1 += 1;
                    part2 += 1;
                    break;
                case 'Y':
                    part1 += 5;
                    part2 += 5;
                    break;
                case 'Z':
                    part1 += 9;
                    part2 += 9;
                    break;
                }
                break;
            case 'C':
                switch (line[2]) {
                case 'X':
                    part1 += 7;
                    part2 += 2;
                    break;
                case 'Y':
                    part1 += 2;
                    part2 += 6;
                    break;
                case 'Z':
                    part1 += 6;
                    part2 += 7;
                    break;
                }
                break;
        }
    }

    cout << endl << "Day 2" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
