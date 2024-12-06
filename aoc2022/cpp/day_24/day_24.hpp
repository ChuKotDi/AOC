#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class BlizzardBasin {
public:
    int mapWidth;
    int mapHeight;
    BlizzardBasin(string filename) {
        ReadMapFromFile(filename);
        InitMapInfo();
    }
    int Simulation(int startX, int startY, int endX, int endY) {
        int moveCount = 0;
        vector<vector<bool>> existMove(mapHeight, vector<bool>(mapWidth));
        existMove[startY][startX] = true;
        bool simulationRun = true;
        //displayExistMove();
        while (simulationRun) {
            moveCount++;
            //cout << "start move :" << moveCount << endl;
            vector<vector<bool>> nextExistMove(mapHeight, vector<bool>(mapWidth));
            nextExistMove = existMove;
            for (auto& blizzard : blizzads) {
                blizzard.Move(mapWidth, mapHeight);
                nextExistMove[blizzard.y][blizzard.x] = false;
            }
            
            for (int y = 0; y < mapHeight; y++) {
                for (int x = 0; x < mapWidth; x++) {
                    if (existMove[y][x]) {
                        for (auto dir : direction) {
                            checkMoveWithAdd(x + dir.first, y + dir.second, nextExistMove);
                        }
                    }
                }
            }
            existMove = nextExistMove;
            //displayExistMove(&existMove);
            if (existMove[endY][endX]) {
                simulationRun = false;
            }
        }
        return moveCount;
    }
private:
    pair<int, int> direction[4] = { {0 ,1}, {1, 0} , {0 , -1}, {-1, 0} };
    vector<string> map;
    struct Blizzard {
        char type;
        int x;
        int y;
        Blizzard(char blizzardType, int posX, int posY) {
            type = blizzardType;
            x = posX;
            y = posY;
        }
        void Move(int mapWidth, int mapHeight) {
            switch (type) {
            case '<':
                x--;
                if (x == 0) {
                    x = mapWidth - 2;
                }
                break;
            case '>':
                x++;
                if (x == mapWidth - 1) {
                    x = 1;
                }
                break;
            case '^':
                y--;
                if (y == 0) {
                    y = mapHeight - 2;
                }
                break;
            case 'v':
                y++;
                if (y == mapHeight - 1) {
                    y = 1;
                }
                break;
            default:
                cout << "Error!!!" << endl;
                break;
            }
        }
    };
    vector<Blizzard> blizzads;
    void ReadMapFromFile(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            if (!line.empty()) {
                map.push_back(line);
            }
        }

        inputFile.close();
    }
    void InitMapInfo() {
        mapHeight = map.size();
        mapWidth = map[0].size();

        for (int y = 1; y < mapHeight - 1; y++) {
            for (int x = 1; x < mapWidth - 1; x++) {
                if (map[y][x] != '.') {
                    Blizzard blizzard(map[y][x], x, y);
                    blizzads.push_back(blizzard);
                }
            }
        }
    }
    void checkMoveWithAdd(int x, int y, vector<vector<bool>> &existMove) {
        if (x >= 0 && y >= 0 && x < mapWidth && y < mapHeight && !existMove[y][x] && map[y][x] != '#') {
            bool check = true;
            for (auto blizzard : blizzads) {
                if (x == blizzard.x && y == blizzard.y) {
                    check = false;
                    break;
                }
            }
            if (check) {
                existMove[y][x] = true;
            }
        }
    }
    void displayExistMove(vector<vector<bool>> *existMove = NULL) {
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                char ch = '.';
                if (map[y][x] == '#') {
                    ch = '#';
                }
                if (existMove != NULL) {
                    if ((*existMove)[y][x]) {
                        ch = 'm';
                    }
                }
                int count = 0;
                for (auto b : blizzads) {
                    if (x == b.x && y == b.y) {
                        count++;
                        ch = b.type;
                    }
                }
                if (count > 1) {
                    ch = '0' + count;
                }
                cout << ch;
            }
            cout << endl;
        }
        cout << endl;
    }
};

void day24_start(string filename) {
    cout << endl << "Day 24" << endl;
    BlizzardBasin blizzardBasin(filename);
    int path1 = blizzardBasin.Simulation(1, 0, blizzardBasin.mapWidth - 2, blizzardBasin.mapHeight - 1);
    cout << "part1: " << path1 << endl;
    int path2 = blizzardBasin.Simulation(blizzardBasin.mapWidth - 2, blizzardBasin.mapHeight - 1, 1, 0);
    int path3 = blizzardBasin.Simulation(1, 0, blizzardBasin.mapWidth - 2, blizzardBasin.mapHeight - 1);
    cout << "part2: " << path1 + path2 + path3 << endl;
    //cout << path1 << endl << path2 << endl << path3 << endl;
}