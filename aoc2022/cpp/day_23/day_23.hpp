#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class UnstableDiffusion {
public:
    UnstableDiffusion(string filename) {
        ReadMapFromFile(filename);
    }
    void DisplayMap(string title) {
        cout << title << endl;
        for (int i = 0; i < mapHeight; i++) {
            cout << map[i] << endl;
        }
        cout << endl;
    }
    void MapSimulation(int stepCount = 10) {
        firstDirection = 0;
        map = mapSave;
        elfs.clear();
        AddMapInfo();
        for (int i = 0; i < stepCount; i++) {
            StepSimulation();
            //stringstream ss;
            //ss << "step " << i + 1;
            //DisplayMap(ss.str());
            firstDirection++;
            firstDirection = firstDirection % directionCount;
        }
    }
    long long InfinityMapSimulation() {
        firstDirection = 0;
        map = mapSave;
        elfs.clear();
        AddMapInfo();
        long long stepCount = 1;
        while (StepSimulation()) {
            stepCount++;
            firstDirection++;
            firstDirection = firstDirection % directionCount;
        }
        return stepCount;
    }
    int GetEmptyGround() {
        int minX = mapWidth, minY = mapHeight, maxX = 0, maxY = 0;
        for (auto elf : elfs) {
            minX = min(minX, elf.x);
            minY = min(minY, elf.y);
            maxX = max(maxX, elf.x);
            maxY = max(maxY, elf.y);
        }
        int count = 0;
        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++) {
                if (map[y][x] != '#') {
                    count++;
                }
            }
        }
        return count;
    }
private:
    vector<string> map;
    vector<string> mapSave;
    int mapWidth;
    int mapHeight;
    int directionCount = 4;
    int firstDirection = 0;
    int mapOffset = 100;
    struct ElfPosition
    {
        int x;
        int y;
        int newX;
        int newY;
    };
    vector<ElfPosition> elfs;
    void ReadMapFromFile(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            map.push_back(line);
        }

        inputFile.close();
        mapSave = map;
    }
    void AddMapInfo() {
        mapHeight = map.size();
        mapWidth = map[0].size();

        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapOffset; j++) {
                map[i].push_back('.');
                map[i].insert(map[i].begin(), '.');
            }
        }
        mapWidth += 2 * mapOffset;

        string emptyFull;
        for (int i = 0; i < mapWidth; i++) {
            emptyFull.push_back('.');
        }

        for (int i = 0; i < mapOffset; i++) {
            map.push_back(emptyFull);
            map.insert(map.begin(), emptyFull);
        }
        mapHeight += 2 * mapOffset;

        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapWidth; j++) {
                if (map[i][j] == '#') {
                    ElfPosition elf;
                    elf.x = j;
                    elf.y = i;
                    elf.newX = elf.x;
                    elf.newY = elf.y;
                    elfs.push_back(elf);
                }
            }
        }
    }
    bool StepSimulation() {
        doFirstHalf();
        return doSecondHalf();
    }
    void doFirstHalf() {
        for (auto& elf : elfs) {
            if (!checkElfAround(elf.x, elf.y)) {
                elf.newX = elf.x;
                elf.newY = elf.y;
            }
            else {
                bool move = false;
                int dir = firstDirection;
                int count = 4;
                while (count > 0 && !move) {
                    count--;
                    switch (dir) {
                    case 0:
                        // Если в соседних позициях N, NE или NW нет Elf, Elf предлагает переместить север один шаг.
                        if (!isElf(elf.x, elf.y - 1) && !isElf(elf.x - 1, elf.y - 1) && !isElf(elf.x + 1, elf.y - 1)) {
                            move = true;
                            elf.newX = elf.x;
                            elf.newY = elf.y - 1;
                        }
                        break;
                    case 1:
                        // Если в соседних позициях S, SE или SW нет Elf, Elf предлагает переместить юг один шаг.
                        if (!isElf(elf.x, elf.y + 1) && !isElf(elf.x - 1, elf.y + 1) && !isElf(elf.x + 1, elf.y + 1)) {
                            move = true;
                            elf.newX = elf.x;
                            elf.newY = elf.y + 1;
                        }
                        break;
                    case 2:
                        // Если в соседних позициях W, NW или SW нет Elf, Elf предлагает переместить запад один шаг.
                        if (!isElf(elf.x - 1, elf.y) && !isElf(elf.x - 1, elf.y - 1) && !isElf(elf.x - 1, elf.y + 1)) {
                            move = true;
                            elf.newX = elf.x - 1;
                            elf.newY = elf.y;
                        }
                        break;
                    case 3:
                        //Если в соседних позициях E, NE или SE нет Elf, Elf предлагает переместить восток один шаг.
                        if (!isElf(elf.x + 1, elf.y) && !isElf(elf.x + 1, elf.y - 1) && !isElf(elf.x + 1, elf.y + 1)) {
                            move = true;
                            elf.newX = elf.x + 1;
                            elf.newY = elf.y;
                        }
                        break;
                    }
                    dir++;
                    dir %= directionCount;
                }
            }
        }
    }
    bool doSecondHalf() {
        bool endCheck = false;
        while (!endCheck) {
            endCheck = true;
            for (auto& elf : elfs) {
                endCheck = endCheck && checkMove(elf);
            }
        }
        bool stepMove = false;

        for (auto& elf : elfs) {
            if (elf.newX != elf.x || elf.newY != elf.y) {
                stepMove = true;
            }
            moveElf(elf);
        }

        return stepMove;
    }
    bool checkMove(ElfPosition& elf) {
        int count = 0;
        if (elf.newX != elf.x || elf.newY != elf.y) {
            for (auto elf2 : elfs) {
                if (elf.newX == elf2.newX && elf.newY == elf2.newY) {
                    count++;
                }
            }
            if (count > 1) {
                int x = elf.newX;
                int y = elf.newY;
                for (auto& elf2 : elfs) {
                    if (x == elf2.newX && y == elf2.newY) {
                        elf2.newX = elf2.x;
                        elf2.newY = elf2.y;
                    }
                }
            }
        }
        return count == 1 || count == 0;
    }
    void moveElf(ElfPosition& elf) {
        if (elf.newX != elf.x || elf.newY != elf.y) {
            map[elf.y][elf.x] = '.';
            map[elf.newY][elf.newX] = '#';
            elf.x = elf.newX;
            elf.y = elf.newY;
        }
    }
    bool isElf(int x, int y) {
        bool result = false;
        if (map[y][x] == '#') {
            result = true;
        }
        return result;
    }
    bool checkElfAround(int x, int y) {
        bool result = isElf(x - 1, y) || isElf(x + 1, y) || isElf(x - 1, y - 1) || isElf(x, y - 1) || isElf(x + 1, y - 1) || isElf(x - 1, y + 1) || isElf(x, y + 1) || isElf(x + 1, y + 1);
        return result;
    }
};

void day23_start(string filename) {
    cout << endl << "Day 23" << endl;
    UnstableDiffusion  unstableDiffusion(filename);
    //unstableDiffusion.DisplayMap("Initial state:");
    unstableDiffusion.MapSimulation(10);
    cout << "part 1: " << unstableDiffusion.GetEmptyGround() << endl;
    //todo: подумать как оптимизировать
    cout << "part 2: " << unstableDiffusion.InfinityMapSimulation() << endl;
}