#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class MonkeyMap {
public:
    MonkeyMap(string filename) {
        ReadMonkeyMapFromFile(filename);
    }
    int GetFinalPassword(bool original = true) {
        int dir = 0;
        int x = find(map[0].begin(), map[0].end(), '.') - map[0].begin();
        int y = 0;

        istringstream iss(followPath);
        int steps;
        char rotate;
        while (iss >> steps) {
            for (int i = 0; i < steps; ++i) {
                if (original) {
                    pathStep(x, y, dir, mapWidth, mapHeight);
                }
                else {
                    pathStep2(x, y, dir, mapWidth, mapHeight);
                }
            }
            if (iss >> rotate) {
                if (rotate == 'L') {
                    dir = (dir + 3) % direction_count;
                }
                else {
                    dir = (dir + 1) % direction_count;
                }
            }
        }
        return 1000 * (y + 1) + 4 * (x + 1) + dir;
    }
private:
    vector<string> map;
    string followPath;
    int mapWidth;
    int mapHeight;
    int direction_count = 4;
    int cubeSize = 50;
    pair<int, int> direction[4] = {{0 ,1}, {1, 0} , {0 , -1}, {-1, 0}};
    void ReadMonkeyMapFromFile(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            map.push_back(line);
        }
        followPath = map.back();
        map.pop_back();
        map.pop_back();

        mapHeight = map.size();
        mapWidth = 0;
        for (int i = 0; i < mapHeight; ++i) {
            mapWidth = max(mapWidth, (int)map[i].size());
        }
        for (int i = 0; i < mapHeight; ++i) {
            while (map[i].size() < mapWidth) {
                map[i] += ' ';
            }
        }

        inputFile.close();
    }

    void pathStep(int &x, int &y, int dir, int width, int height) {
        int sx = x, sy = y;
        do {
            x += direction[dir].second;
            y += direction[dir].first;
            x = (x + width) % width;
            y = (y + height) % height;
            if (map[y][x] == '.') {
                sx = x, sy = y;
            }
        } while (map[y][x] == ' ');
        x = sx, y = sy;
    };
    void pathStep2(int& x, int& y, int& dir, int width, int height) {
        int sx = x, sy = y, sdir = dir;
        x += direction[dir].second;
        y += direction[dir].first;
        x = (x + width) % width;
        y = (y + height) % height;
        /*
        .12
        .3.
        54.
        6..
        */
        switch (dir) {
        case 0:
            // 2>
            if (x == 0 && y < 1 * cubeSize && y >= 0) {
                dir = 2; // <
                y = (cubeSize - (y - 0 * cubeSize) - 1) + 2 * cubeSize;
                x = 2 * cubeSize - 1;
            }
            // 3>
            else if (x == 2 * cubeSize && y < 2 * cubeSize && y >= 1 * cubeSize) {
                dir = 3; // ^
                x = (y - 1 * cubeSize) + 2 * cubeSize;
                y = 1 * cubeSize - 1;
            }
            // 4>
            else if (x == 2 * cubeSize && y < 3 * cubeSize && y >= 2 * cubeSize) {
                dir = 2; // <
                y = (cubeSize - (y - 2 * cubeSize) - 1) + 0 * cubeSize;
                x = 3 * cubeSize - 1;
            }
            // 6>
            else if (x == 1 * cubeSize && y < 4 * cubeSize && y >= 3 * cubeSize) {
                dir = 3; // ^
                x = (y - 3 * cubeSize) + 1 * cubeSize;
                y = 3 * cubeSize - 1;
            }
            break;
        case 1:
            // 2v
            if (y == 1 * cubeSize && x < 3 * cubeSize && x >= 2 * cubeSize) {
                dir = 2;
                y = (x - 2 * cubeSize) + 1 * cubeSize;
                x = 2 * cubeSize - 1;
            }
            // 4v
            else if (y == 3 * cubeSize && x < 2 * cubeSize && x >= 1 * cubeSize) {
                dir = 2; // <
                y = (x - 1 * cubeSize) + 3 * cubeSize;
                x = 1 * cubeSize - 1;
            }
            // 6v
            else if (y == 0 && x < 1 * cubeSize && x >= 0) {
                y = 0;
                x += 2 * cubeSize;
            }
            break;
        case 2:
            // 1<
            if (x == 1 * cubeSize - 1 && y < 1 * cubeSize && y >= 0) {
                dir = 0; // v
                y = (cubeSize - (y - 0 * cubeSize) - 1) + 2 * cubeSize;
                x = 0;
            }
            // 3< -> (top of 5)
            else if (x == 1 * cubeSize - 1 && y < 2 * cubeSize && y >= 1 * cubeSize) {
                dir = 1; // v
                x = (y - 1 * cubeSize) + 0 * cubeSize;
                y = 2 * cubeSize;
            }
            // 5<
            else if (x == 3 * cubeSize - 1 && y < 3 * cubeSize && y >= 2 * cubeSize) {
                dir = 0; // >
                y = (cubeSize - (y - 2 * cubeSize) - 1) + 0 * cubeSize;
                x = 1 * cubeSize;
            }
            // 6<
            else if (x == 3 * cubeSize - 1 && y < 4 * cubeSize && y >= 3 * cubeSize) {
                dir = 1; // v
                x = (y - 3 * cubeSize) + 1 * cubeSize;
                y = 0;
            }
            break;
        case 3:
            // 1^
            if (y == 4 * cubeSize - 1 && x < 2 * cubeSize && x >= 1 * cubeSize) {
                dir = 0; // >
                y = (x - 1 * cubeSize) + 3 * cubeSize;
                x = 0 * cubeSize;
            }
            // 2^
            else if (y == 4 * cubeSize - 1 && x < 3 * cubeSize && x >= 2 * cubeSize) {
                x -= 2 * cubeSize;
            }
            // 5^
            else if (y == 2 * cubeSize - 1 && x < 1 * cubeSize && x >= 0) {
                dir = 0; // >
                y = (x - 0 * cubeSize) + 1 * cubeSize;
                x = 1 * cubeSize;
            }
            break;
        }

        if (map[y][x] != '#') {
            sx = x, sy = y, sdir = dir;
        }
        x = sx, y = sy, dir = sdir;
    };
};

void day22_start(string filename) {
    cout << endl << "Day 22" << endl;
    MonkeyMap monkeyMap(filename);
    cout << "part 1: " << monkeyMap.GetFinalPassword() << endl;
    cout << "part 2: " << monkeyMap.GetFinalPassword(false) << endl;
}