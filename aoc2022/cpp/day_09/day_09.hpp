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

struct comandLine {
    char dir = 'x';
    int count = 0;
};

void day9_start(string filename) {
    // TODO: переписать, отказаться от карты видимости.
    // Видимость искать для каждого элемента поиском по направлениям. (чтобы объединить первую и вторую часть)
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл не найден Оо" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    vector<comandLine> comands;
    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    int curX = 0, curY = 0;
    while (!inputFile.eof()) {
        comandLine line;
        inputFile >> line.dir >> line.count;
        if (line.dir == 'x') {
            break;
        }
        comands.push_back(line);
        switch (line.dir) {
            case 'R':
                curX += line.count;
                if (curX > maxX) {
                    maxX = curX;
                }
                break;
            case 'L':
                curX -= line.count;
                if (curX < minX) {
                    minX = curX;
                }
                break;
            case 'U':
                curY += line.count;
                if (curY > maxY) {
                    maxY = curY;
                }
                break;
            case 'D':
                curY -= line.count;
                if (curY < minY) {
                    minY = curY;
                }
                break;
        }
    }

    vector<vector<int>> map1;
    vector<vector<int>> map9;
    for (int i = minY; i <= maxY; i++) {
        vector<int> line;
        for (int j = minX; j <= maxX; j++) {
            line.push_back(0);
        }
        map1.push_back(line);
        map9.push_back(line);
    }

    int headX = -minX, headY = -minY;
    const int snakeLength = 10;
    int snakeX[snakeLength];
    int snakeY[snakeLength];
    for (int i = 0; i < snakeLength; i++) {
        snakeX[i] = headX;
        snakeY[i] = headY;
    }
    map1[snakeY[0]][snakeX[0]] = 3;
    map9[snakeY[0]][snakeX[0]] = 3;

    for (int i = 0; i <  comands.size(); i++) {
        int count = comands[i].count;
        while (count != 0) {
            count--;
            switch (comands[i].dir) {
                case 'R':
                    snakeX[0]++;
                    break;
                case 'L':
                    snakeX[0]--;
                    break;
                case 'U':
                    snakeY[0]++;
                    break;
                case 'D':
                    snakeY[0]--;
                    break;
            }
            for (int k = 1; k < snakeLength; k++) {
                int dirX = snakeX[k - 1] - snakeX[k];
                int offsetX = abs(dirX);
                int dirY = snakeY[k - 1] - snakeY[k];
                int offsetY = abs(dirY);
                if (offsetX > 1 && offsetY == 0) {
                    snakeX[k] += dirX > 0 ? 1 : -1;
                    if (k == 1) {
                        map1[snakeY[k]][snakeX[k]] = k;
                    }
                    if (k == 9) {
                        map9[snakeY[k]][snakeX[k]] = k;
                    }
                }
                else if (offsetY > 1 && offsetX == 0) {
                    snakeY[k] += dirY > 0 ? 1 : -1;
                    if (k == 1) {
                        map1[snakeY[k]][snakeX[k]] = k;
                    }
                    if (k == 9) {
                        map9[snakeY[k]][snakeX[k]] = k;
                    }
                }
                else if (offsetX > 1 && offsetY == 1 || offsetY > 1 && offsetX == 1 || offsetY == 2 && offsetX == 2) {
                    snakeX[k] += dirX > 0 ? 1 : -1;
                    snakeY[k] += dirY > 0 ? 1 : -1;
                    if (k == 1) {
                        map1[snakeY[k]][snakeX[k]] = k;
                    }
                    if (k == 9) {
                        map9[snakeY[k]][snakeX[k]] = k;
                    }
                }
            }
        }
    }

    part1 = 0;
    part2 = 0;
    for (int i = 0; i < map1.size(); i++) {
        for (int j = 0; j < map1[i].size(); j++) {
            if (map1[i][j] > 0) {
                part1++;
            }
            if (map9[i][j] > 0) {
                part2++;
            }
        }
    }

    cout << endl << "Day 9" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;

    inputFile.close();
}
