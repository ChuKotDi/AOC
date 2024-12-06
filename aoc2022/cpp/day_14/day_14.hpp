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

const int MAX_HEIGTH = 1000;
const int MAX_WIDTH = 1000;
const int DUST_START_X = 500;
const int DUST_START_Y = 0;
const int OFFSET_MAP_X = 50;
const int OFFSET_MAP_Y = 2;
const char OXIGEN_PIC = '.';
const char DUST_START_PIC = '+';
const char DUST_PIC = 'o';
const char STONE_PIC = '#';

struct point {
    int x;
    int y;
    point(int pointX, int pointY) {
        x = pointX;
        y = pointY;
    }
};

vector<point> getStonesLine(string line) {
    line = regex_replace(line, regex(" -> "), " ");
    vector<string> tokens;
    string token;

    for (const auto& c : line) {
        if (!isspace(c) && c != ',') {
            token += c;
        }
        else {
            if (token.length()) {
                tokens.push_back(token);
            }
            token.clear();
        }
    }

    if (token.length()) {
        tokens.push_back(token);
    }

    vector<point> stoneLine;
    for (int i = 0; i < tokens.size(); i += 2) {
        point stoneGoalPoint(stoi(tokens[i]), stoi(tokens[i + 1]));
        stoneLine.push_back(stoneGoalPoint);
    }
    return stoneLine;
}

void setMinMaxPoint(point currentPoint, point* minPoint, point* maxPoint) {
    if (currentPoint.x < minPoint->x) {
        minPoint->x = currentPoint.x;
    }
    if (currentPoint.y < minPoint->y) {
        minPoint->y = currentPoint.y;
    }
    if (currentPoint.x > maxPoint->x) {
        maxPoint->x = currentPoint.x;
    }
    if (currentPoint.y > maxPoint->y) {
        maxPoint->y = currentPoint.y;
    }
}

void drawStoneLine(vector<point> stoneLine, vector<vector<char>>* worldMap, point* minWorldMapPoint, point* maxWorldMapPoint) {
    setMinMaxPoint(stoneLine[0], minWorldMapPoint, maxWorldMapPoint);
    for (int i = 1; i < stoneLine.size(); i++) {
        setMinMaxPoint(stoneLine[i], minWorldMapPoint, maxWorldMapPoint);
        int startX = stoneLine[i - 1].x;
        int startY = stoneLine[i - 1].y;
        int endX = stoneLine[i].x;
        int endY = stoneLine[i].y;
        if (startX == endX) {
            int begin = startY < endY ? startY : endY;
            int end = startY > endY ? startY : endY;

            for (int y = begin; y <= end; y++) {
                (*worldMap)[y][startX] = STONE_PIC;
            }
        }
        else if (startY == endY) {
            int begin = startX < endX ? startX : endX;
            int end = startX > endX ? startX : endX;
            for (int x = begin; x <= end; x++) {
                (*worldMap)[startY][x] = STONE_PIC;
            }
        }
    }
}

void displayMap(vector<vector<char>>* worldMap, point minPoint, point maxPoint, string title) {
    cout << title << endl;
    for (int y = minPoint.y; y <= maxPoint.y + OFFSET_MAP_Y; y++) {
        for (int x = minPoint.x - OFFSET_MAP_X; x <= maxPoint.x + OFFSET_MAP_X; x++) {
            cout << (*worldMap)[y][x];
        }
        cout << endl;
    }
}

bool checkPoint(vector<vector<char>>* worldMap, int x, int y) {
    bool result = true;

    if ((*worldMap)[y][x] == DUST_PIC || (*worldMap)[y][x] == STONE_PIC) {
        result = false;
    }
    return result;
}

int emulate(vector<vector<char>>* worldMap, point maxWorldMapPoint) {
    int dustCount = 0;

    bool emulate = true;
    point dustPosition(DUST_START_X, DUST_START_Y);
    while (emulate) {
        if (dustPosition.y > maxWorldMapPoint.y) {
            emulate = false;
        }

        if (checkPoint(worldMap, dustPosition.x, dustPosition.y + 1)) {
            dustPosition.y += 1;
        }
        else if (checkPoint(worldMap, dustPosition.x - 1, dustPosition.y + 1)) {
            dustPosition.x -= 1;
            dustPosition.y += 1;
        }
        else if (checkPoint(worldMap, dustPosition.x + 1, dustPosition.y + 1)) {
            dustPosition.x += 1;
            dustPosition.y += 1;
        }
        else {
            if (checkPoint(worldMap, dustPosition.x, dustPosition.y)) {
                (*worldMap)[dustPosition.y][dustPosition.x] = DUST_PIC;
                dustPosition.x = DUST_START_X;
                dustPosition.y = DUST_START_Y;
                dustCount++;
            }
            else {
                emulate = false;
            }
        }
    }

    return dustCount;
}
void day14_start(string filename) {
    cout << endl << "Day 14" << endl;
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл потерялся оО" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    vector<vector<char>> worldMap(MAX_HEIGTH, vector<char>(MAX_WIDTH, OXIGEN_PIC));
    vector<vector<char>> worldMap2(MAX_HEIGTH, vector<char>(MAX_WIDTH, OXIGEN_PIC));
    point minWorldMapPoint(DUST_START_X, DUST_START_Y);
    point maxWorldMapPoint(DUST_START_X, DUST_START_Y);
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);

        if (!line.empty()) {
            vector<point> stoneLine = getStonesLine(line);
            drawStoneLine(stoneLine, &worldMap, &minWorldMapPoint, &maxWorldMapPoint);
        }
    }

    worldMap2 = worldMap;
    part1 = emulate(&worldMap, maxWorldMapPoint);
    displayMap(&worldMap, minWorldMapPoint, maxWorldMapPoint, "End map state for emulate 1:");

    maxWorldMapPoint.y += 2;
    for (int x = 0; x < MAX_WIDTH; x++) {
        worldMap2[maxWorldMapPoint.y][x] = STONE_PIC;
    }
    part2 = emulate(&worldMap2, maxWorldMapPoint);
    //displayMap(&worldMap2, minWorldMapPoint, maxWorldMapPoint, "End map state fo emulate 2:");
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
