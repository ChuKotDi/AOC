#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class BoilingBoulders
{
public:
    BoilingBoulders(string filename) {
        getDropsOfLavaFromFile(filename);
    }

    int getDropsOfLavaSquare(bool needCheckAirPockets = false) {
        lavaSquare.clear();
        for (auto item : dropsOfLava) {
            if (!dropsOfLava.count({ item.x - 1, item.y, item.z })) {
                lavaSquare.insert({ item.x - 1, item.y, item.z });
            }
            if (!dropsOfLava.count({ item.x + 1, item.y, item.z })) {
                lavaSquare.insert({ item.x + 1, item.y, item.z });
            }
            if (!dropsOfLava.count({ item.x, item.y - 1, item.z })) {
                lavaSquare.insert({ item.x, item.y - 1, item.z });
            }
            if (!dropsOfLava.count({ item.x, item.y + 1, item.z })) {
                lavaSquare.insert({ item.x, item.y + 1, item.z });
            }
            if (!dropsOfLava.count({ item.x, item.y, item.z - 1 })) {
                lavaSquare.insert({ item.x, item.y, item.z - 1 });
            }
            if (!dropsOfLava.count({ item.x, item.y, item.z + 1 })) {
                lavaSquare.insert({ item.x, item.y, item.z + 1 });
            }
        }
        int count = 0;
        if (needCheckAirPockets) {
            for (auto drop: lavaSquare) {
                bool interest = true;
                const int maxDistance = 30;
                bool checkUpX = true;
                bool checkDownX = true;
                bool checkUpY = true;
                bool checkDownY = true;
                bool checkUpZ = true;
                bool checkDownZ = true;
                for (int i = 1; i < maxDistance && interest; i++) {
                    if (checkUpX && dropsOfLava.count({ drop.x - i, drop.y, drop.z })) {
                        checkUpX = false;
                    }
                    if (checkDownX && dropsOfLava.count({ drop.x + i, drop.y, drop.z })) {
                        checkDownX = false;
                    }
                    if (checkUpY && dropsOfLava.count({ drop.x, drop.y - i, drop.z })) {
                        checkUpY = false;
                    }
                    if (checkDownY && dropsOfLava.count({ drop.x, drop.y + i, drop.z })) {
                        checkDownY = false;
                    }
                    if (checkUpZ && dropsOfLava.count({ drop.x, drop.y, drop.z - i})) {
                        checkUpZ = false;
                    }
                    if (checkDownZ && dropsOfLava.count({ drop.x, drop.y, drop.z + i })) {
                        checkDownZ = false;
                    }
                    if (checkUpX || checkDownX || checkUpY || checkDownY || checkUpZ || checkDownZ) {
                        interest = true;
                    }
                    else {
                        interest = false;
                        vector<point> queue;
                        const int maxCount = 2000;
                        set<point> seen;
                        seen.insert({ drop.x, drop.y, drop.z });;
                        queue.push_back({ drop.x, drop.y, drop.z });
                        while (!queue.empty() && seen.size() <= maxCount) {
                            auto cur = queue[0];
                            queue.erase(queue.begin());
                            if (!dropsOfLava.count({ cur.x - 1, cur.y, cur.z }) && !seen.count({ cur.x - 1, cur.y, cur.z })) {
                                seen.insert({ cur.x - 1, cur.y, cur.z });
                                queue.push_back({ cur.x - 1, cur.y, cur.z });
                            }
                            if (!dropsOfLava.count({ cur.x + 1, cur.y, cur.z }) && !seen.count({ cur.x + 1, cur.y, cur.z })) {
                                seen.insert({ cur.x + 1, cur.y, cur.z });
                                queue.push_back({ cur.x + 1, cur.y, cur.z });
                            }
                            if (!dropsOfLava.count({ cur.x, cur.y - 1, cur.z }) && !seen.count({ cur.x, cur.y - 1, cur.z })) {
                                seen.insert({ cur.x, cur.y - 1, cur.z });
                                queue.push_back({ cur.x, cur.y - 1, cur.z });
                            }
                            if (!dropsOfLava.count({ cur.x, cur.y + 1, cur.z }) && !seen.count({ cur.x, cur.y + 1, cur.z })) {
                                seen.insert({ cur.x, cur.y + 1, cur.z });
                                queue.push_back({ cur.x, cur.y + 1, cur.z });
                            }
                            if (!dropsOfLava.count({ cur.x, cur.y, cur.z - 1 }) && !seen.count({ cur.x, cur.y, cur.z - 1 })) {
                                seen.insert({ cur.x, cur.y, cur.z - 1 });
                                queue.push_back({ cur.x, cur.y, cur.z - 1 });
                            }
                            if (!dropsOfLava.count({ cur.x, cur.y, cur.z + 1 }) && !seen.count({ cur.x, cur.y, cur.z + 1 })) {
                                seen.insert({ cur.x, cur.y, cur.z + 1 });
                                queue.push_back({ cur.x, cur.y, cur.z + 1 });
                            }
                        }
                        if (seen.size() > maxCount) {
                            count++;
                        }
                    }
                }
                if (interest) {
                    count++;
                }
            }
        }
        else {
            count = lavaSquare.size();
        }

        return count;
    }
private:
    struct point {
        int x, y, z;
        bool operator<(const point& other) const {
            return tie(x, y, z) < tie(other.x, other.y, other.z);
        }
    };
    set<point> dropsOfLava;
    multiset<point> lavaSquare;

    void getDropsOfLavaFromFile(string filename) {
        ifstream inputFile(filename);
        char ch;
        int x, y, z;
        while (inputFile >> x >> ch >> y >> ch >> z) {
            dropsOfLava.insert({ x, y, z });
        }
        inputFile.close();
    }
};

void day18_start(string filename) {
    cout << endl << "Day 18" << endl;
    BoilingBoulders boilingBoulders(filename);
    cout << "part 1: " << boilingBoulders.getDropsOfLavaSquare() << endl;
    //todo: подумать над ускорением
    cout << "part 2: " << boilingBoulders.getDropsOfLavaSquare(true) << endl;
}
