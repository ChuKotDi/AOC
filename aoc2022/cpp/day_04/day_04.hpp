#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>

using namespace std;

void day4_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
    }

    int part1{ 0 }, part2{ 0 };
    while (!inputFile.eof()) {
        char musor;
        int a, b, c, d;
        inputFile >> a >> musor >> b >> musor >> c >> musor >> d;
        if ((a >= c && b <= d) || (c >= a && d <= b)) {
            part1++;
        }
        if ((a <= c && b >= c) || (c <= a && d >= a)) {
            part2++;
        }
    }

    cout << endl << "Day 4" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
