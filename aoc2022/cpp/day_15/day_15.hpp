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
#include <regex>

using namespace std;

class sensor {
    public:
        long x = 0;
        long y = 0;
        long beconX = 0;
        long beconY = 0;
        long sensorDistance = 0;
        sensor(string sensorInitionString) {
            vector<long> numbers = this->getStartNumbersFromString(sensorInitionString);
            if (numbers.size() == 4) {
                this->x = numbers[0];
                this->y = numbers[1];
                this->beconX = numbers[2];
                this->beconY = numbers[3];
                this->sensorDistance = abs(this->beconX - this->x) + abs(this->beconY - this->y);
            }
        }
        bool checkCoverageSensor(long x, long y) {
            bool result = false;
            long distance = abs(x - this->x) + abs(y - this->y);

            if (distance <= this->sensorDistance)
            {
                result = true;
            }

            return result;
        }
    private:
        vector<long> getStartNumbersFromString(string str) {
            vector<long> numbers;
            long number = 0;
            int signNumber = 1;
            bool exist = false;
            for (long i = 0; i <= str.size(); i++) {
                if (i < str.size() && str[i] >= '0' && str[i] <= '9') {
                    number *= 10;
                    number += (int)str[i] - (int)'0';
                    exist = true;
                }
                else if (i < str.size() && str[i] == '-') {
                    signNumber = -1;
                }
                else {
                    if (exist) {
                        number *= signNumber;
                        numbers.push_back(number);
                        number = 0;
                        signNumber = 1;
                        exist = false;
                    }
                }
            }
            return numbers;
        }
};

void getMetricsFromSensors(long& minX, long& maxX, vector<sensor> *sensors) {
    minX = 0;
    maxX = 0;
    for (int i = 0; i < (*sensors).size(); i++) {
        sensor bipPub = (*sensors)[i];
        long x = bipPub.x - bipPub.sensorDistance;
        if (minX > x) {
            minX = x;
        }
        x = bipPub.x + bipPub.sensorDistance;
        if (maxX < x) {
            maxX = x;
        }
    }
}

void day15_start(string filename) {
    // todo: подумать как можно ускорить
    cout << endl << "Day 15" << endl;

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл потерялся оО" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    vector<sensor> mapSensors;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);

        if (!line.empty()) {
            sensor bipPub(line);
            mapSensors.push_back(bipPub);
        }
    }
    long maxDistance = 0;
    long maxX, minX;
    getMetricsFromSensors(minX, maxX, &mapSensors);
    long count = 0;
    long searchY = 2000000;
    for (long x = minX; x <= maxX; x++) {
        bool isFind = false;
        for (int i = 0; i < mapSensors.size(); i++) {
            if (mapSensors[i].checkCoverageSensor(x, searchY)) {
                isFind = true;
            }
            if (mapSensors[i].beconX == x && mapSensors[i].beconY == searchY) {
                isFind = false;
                break;
            }
        }
        if (isFind) {
            count++;
        }
    }
    part1 = count;
    cout << "part 1: " << part1 << endl;

    long long freq = 0;
    string ans = "";
    for (long y = 0; y <= 4000000 && freq == 0; y++) {
        vector<long> start;
        vector<long> end;
        for (int i = 0; i < mapSensors.size(); i++) {
            long dist = mapSensors[i].sensorDistance - abs(y - mapSensors[i].y);
            if (dist >= 0) {
                start.push_back(mapSensors[i].x - dist);
                end.push_back(mapSensors[i].x + dist);
            }
        }
        bool change = true, find = false;
        long x = 0;
        while (change) {
            change = false;
            for (int i = 0; i < start.size(); i++) {
                if (x >= start[i] && x <= end[i]) {
                    x = end[i] + 1;
                    start.erase(start.begin() + i);
                    end.erase(end.begin() + i);
                    change = true;
                    find = true;
                    break;
                }
            }
        }
        if (find && x <= 4000000 && x >= 0) {
            freq = 4 * x + y / 1000000;
            ans = to_string(freq) + to_string(y % 1000000);
            break;
        }
    }
    cout << "part 2: " << ans << endl;
    inputFile.close();
}
