#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>

using namespace std;

void day1_start(string filename){
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл не найден Оо" << endl;
    }

    int tally{0};
    multiset<int, std::greater<int>> calorie_totals;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        if (line.empty()) {
            calorie_totals.insert(tally);
            tally = 0;
            continue;
        }

        tally += stoi(line);
    }

    cout << endl << "Day 1" << endl;
    cout << "part 1: " << *calorie_totals.begin() << endl;
    cout << "part 2: " << *calorie_totals.begin() + *next(calorie_totals.begin()) + *next(calorie_totals.begin(),2) << endl;
    inputFile.close();
}
