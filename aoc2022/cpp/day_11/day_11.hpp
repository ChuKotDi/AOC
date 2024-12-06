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

vector<long long> getNumberFromString(string str) {
    vector<long long> numbers;
    int number = -1;
    int zeroCode = (int)'0';
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (number == -1) {
                number = 0;
            }
            else {
                number *= 10;
            }
            number += (int)str[i] - zeroCode;
        }
        else {
            if (number != -1) {
                numbers.push_back((long long)number);
                number = -1;
            }
        }
    }
    if (number != -1) {
        numbers.push_back((long long)number);
    }
    
    return numbers;
}

class Monkey;

vector <Monkey> monkeys;

class Monkey
{
public:
    Monkey(int monkeyNumber) {
        this->monkeyNumber = monkeyNumber;
    }
    ~Monkey() {
    }
    void setStartingItems(string startingItemsString) {
        vector<long long> numbers = getNumberFromString(startingItemsString);

        for (int i = 0; i < numbers.size(); i++) {
            this->items.push_back(numbers[i]);
        }
    }
    void setOperation(string operationString) {
        operation = operationString;
    }
    void setDivisibleNumber(string s) {
        vector<long long> numbers = getNumberFromString(s);
        this->divisibleNumberForTest = numbers[0];
    }
    void setMonkeyForTrueResultTest(string s) {
        vector<long long> numbers = getNumberFromString(s);
        this->monkeyForTrueResultTest = numbers[0];
    }
    void setMonkeyForFalseResultTest(string s) {
        vector<long long> numbers = getNumberFromString(s);
        this->monkeyForFalseResultTest = numbers[0];
    }

    void work(bool needDiv = true) {
        while (!this->items.empty()) {
            long long item = this->items.front();
            this->items.pop_front();
            item = operationWork(item);
            if (needDiv) {
                item /= 3;
            }
            else {
                long long mods = 1;
                for (int monkeyIndex = 0; monkeyIndex < monkeys.size(); monkeyIndex++) {
                    mods *= monkeys[monkeyIndex].getDivisibleNumber();
                }
                item %= mods;
            }
            if (item % this->divisibleNumberForTest == 0) {
                monkeys[this->monkeyForTrueResultTest].addItem(item);
            }
            else {
                monkeys[this->monkeyForFalseResultTest].addItem(item);
            }
            operationCount++;
        }
    }

    void addItem(long long  item) {
        this->items.push_back(item);
    }

    void displayItems() {
        cout << "Monkey " << this->monkeyNumber << "(" << this->operationCount << ")" << ":";
        if (this->items.size() == 0) {
            cout << " empty";
        }
        else {
            for (list<long long>::iterator it = this->items.begin(); it != this->items.end(); it++) {
                cout << " [" << (*it) << "]";
            }
        }
        cout << endl;
    }
    int operationCount = 0;
    int getDivisibleNumber() {
        return this->divisibleNumberForTest;
    }
private:
    int monkeyNumber;
    list<long long> items;
    string operation;
    int divisibleNumberForTest = 1;
    int monkeyForTrueResultTest = 0;
    int monkeyForFalseResultTest = 0;
    long long operationWork(long long  oldNumber) {
        // ������ ��������� ��� � ��� ������� �������� � ����� ������������� ��������� � �����
        // todo: ���������� �� ����������� ������ � ����������
        long long  newNumber = oldNumber;
        vector<long long> numbers = getNumberFromString(this->operation);
        long long number = numbers.size() == 1 ? numbers[0] : oldNumber;
        for (int i = 0; i < this->operation.size(); i++) {
            switch (this->operation[i])
            {
            case '*':
                newNumber *= number;
                break;
            case '/':
                newNumber /= number;
                break;
            case '+':
                newNumber += number;
                break;
            case '-':
                newNumber -= number;
                break;
            }
        }
        return newNumber;
    }
};

long long getBisnesLevel(vector<Monkey> *monkeyBisnes) {
    vector<long long> operationCount;
    for (int monkeyIndex = 0; monkeyIndex < monkeyBisnes->size(); monkeyIndex++) {
        operationCount.push_back((*monkeyBisnes)[monkeyIndex].operationCount);
    }
    sort(operationCount.begin(), operationCount.end());
    int size = operationCount.size() - 1;
    return operationCount[size - 1] * operationCount[size];
}

void day11_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл потерялся оО" << endl;
        return;
    }

    long long part1{ 0 }, part2{ 0 };
    int monkeyNumber = 0;
    vector<Monkey> saveMonkey;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);

        if (!line.empty()) {
            Monkey monkey(monkeyNumber++);

            getline(inputFile, line);
            monkey.setStartingItems(line);
            getline(inputFile, line);
            monkey.setOperation(line);
            getline(inputFile, line);
            monkey.setDivisibleNumber(line);
            getline(inputFile, line);
            monkey.setMonkeyForTrueResultTest(line);
            getline(inputFile, line);
            monkey.setMonkeyForFalseResultTest(line);

            saveMonkey.push_back(monkey);
        }
    }
    monkeys = saveMonkey;

    int maxStep = 20;

    for (int step = 0; step < 20; step++) {
        for (int monkeyIndex = 0; monkeyIndex < monkeys.size(); monkeyIndex++) {
            monkeys[monkeyIndex].work();
        }
    }
    part1 = getBisnesLevel(&monkeys);

    monkeys = saveMonkey;
    for (int step = 0; step < 10000; step++) {
        //cout << "step: " << step + 1 << endl;
        for (int monkeyIndex = 0; monkeyIndex < monkeys.size(); monkeyIndex++) {
            monkeys[monkeyIndex].work(false);
        }
        //for (int monkeyIndex = 0; monkeyIndex < monkeys.size(); monkeyIndex++) {
        //    monkeys[monkeyIndex].displayItems();
        //}
    }

    part2 = getBisnesLevel(&monkeys);
    cout << endl << "Day 11" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
