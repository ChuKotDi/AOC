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

void day8_start(string filename) {
    // TODO: переписать, отказаться от карты видимости.
    // Видимость искать для каждого элемента поиском по направлениям. (чтобы объединить первую и вторую часть)
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл не найден Оо" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    vector<vector<char>> treeMap;
    vector<vector<int>> pointMap;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        if (line.empty()) {
            break;
        }
        vector<char> treeLine;
        vector<int> pointLine;

        for (char tree : line) {
            treeLine.push_back(tree);
            pointLine.push_back(0);
        }
        treeMap.push_back(treeLine);
        pointMap.push_back(pointLine);
    };

    pointMap[0][0] = 1;
    pointMap[0][treeMap[0].size() - 1] = 1;
    pointMap[treeMap.size() - 1][0] = 1;
    pointMap[treeMap.size() - 1][treeMap[treeMap.size() - 1].size() - 1] = 1;

    for (int i = 1; i < treeMap.size() - 1; i++) {
        int maxX1 = (int)treeMap[i][0];
        int maxX2 = (int)treeMap[i][treeMap.size() - 1];
        pointMap[i][0] = 1;
        pointMap[i][treeMap.size() - 1] = 1;
        for (int j = 1; j < treeMap[i].size() - 1; j++) {
            if (maxX1 < (int)treeMap[i][j]) {
                maxX1 = (int)treeMap[i][j];
                pointMap[i][j]++;
            }
            if (maxX2 < (int)treeMap[i][treeMap.size() - 1 - j]) {
                maxX2 = (int)treeMap[i][treeMap.size() - 1 - j];
                pointMap[i][treeMap.size() - 1 - j]++;
            }
        }
    }

    for (int i = 1; i < treeMap[0].size() - 1; i++) {
        int maxY1 = (int)treeMap[0][i];
        int maxY2 = (int)treeMap[treeMap[0].size() - 1][i];
        pointMap[0][i] = 1;
        pointMap[treeMap[0].size() - 1][i] = 1;
        for (int j = 1; j < treeMap.size() - 1; j++) {
            if (maxY1 < (int)treeMap[j][i]) {
                maxY1 = (int)treeMap[j][i];
                pointMap[j][i]++;
            }
            if (maxY2 < (int)treeMap[treeMap[0].size() - 1 - j][i]) {
                maxY2 = (int)treeMap[treeMap[0].size() - 1 - j][i];
                pointMap[treeMap[0].size() - 1 - j][i]++;
            }
        }
    }

    int visionTreeNumber = 0;
    int beuty = 0;
    for (int i = 0; i < pointMap.size(); i++) {
        for (int j = 0; j < pointMap[i].size(); j++) {
            if (pointMap[i][j] > 0) {
                visionTreeNumber++;
            }
        }
    }
    for (int i = 0; i < pointMap.size(); i++) {
        for (int j = 0; j < pointMap[i].size(); j++) {
            int moms = 0;
            if (pointMap[i][j] > 0) {
                int max2 = (int)treeMap[i][j];
                int down = 0;
                for (int k = i - 1; k >= 0; k--) {
                    down++;
                    if ((int)treeMap[k][j] >= max2) {
                        break;
                    }
                }
                int up = 0;
                for (int k = i + 1; k < pointMap.size(); k++) {
                    up++;
                    if ((int)treeMap[k][j] >= max2) {
                        break;
                    }
                }
                int right = 0;
                for (int k = j + 1; k < pointMap[0].size(); k++) {
                    right++;

                    if ((int)treeMap[i][k] >= max2) {
                        break;
                    }
                }
                int left = 0;
                for (int k = j - 1; k >= 0 ; k--) {
                    left++;
                    if ((int)treeMap[i][k] >= max2) {
                        break;
                    }
                }
                moms = up * down * left * right;
                if (beuty < moms) {
                    beuty = moms;
                }
            }
        }
    }
    part1 = visionTreeNumber;
    part2 = beuty;
    cout << endl << "Day 8" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;

    inputFile.close();
}
