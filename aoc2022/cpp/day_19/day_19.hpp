#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

const long long TIME_MAX = 32;
struct State {
    long long ore, oreRobots, clay, clayRobots, obsidian, obsidianRobots, geodeRobots;
    
    bool operator<(const State& o) const {
        if (geodeRobots < o.geodeRobots) {
            return true;
        }
        else if (geodeRobots == o.geodeRobots) {
            if (obsidian < o.obsidian) {
                return true;
            }
            else if (obsidian == o.obsidian) {
                if (obsidianRobots < o.obsidianRobots) {
                    return true;
                }
                else if (obsidianRobots == o.obsidianRobots) {
                    if (clay < o.clay) {
                        return true;
                    }
                    else if (clay == o.clay) {
                        if (clayRobots < o.clayRobots) {
                            return true;
                        }
                        else if (clayRobots == o.clayRobots) {
                            if (ore < o.ore) {
                                return true;
                            }
                            else if (ore == o.ore && oreRobots < o.oreRobots) {
                                return true;
                            }
                        }
                    }
                }
            }
        }

        return false;
    }
};
map<State, long long> cache[TIME_MAX + 1];

class NotEnoughMinerals {
public:
    NotEnoughMinerals(string filename) {
        getPlansFromFiles(filename);
    }
    long long getSumQuality(long long time) {
        long long sumQuality = 0;
        //cout << "************************* PART1 *****************************" << endl;
        for (auto plan : plans) {
            unsigned long long start_time = clock();
            clearCache(plan);
            //cout << "planId: " << plan.id << endl;
            long long minOre = min(plan.clayRobotCostOre, plan.oreRobotCostOre);
            long long res =  dfs(plan.id - 1, time - minOre, 1, 0, 0, 0, minOre, 0, 0, 0) * plan.id;
            //cout << "quality: " << res << endl;
            sumQuality += res;
            unsigned long long end_time = clock();
            unsigned long long time = end_time - start_time;
            //cout << "time: " << time / 1000.0 << endl << endl;
        }
        return sumQuality;
    }
    long long getSumQuality2(long long time) {
        long long sumQuality2 = 1;
        cout << endl;
        //cout << "************************* PART2 *****************************" << endl;
        for (auto plan : plans) {
            if (plan.id <= 3) {
                unsigned long long start_time = clock();
                clearCache(plan);
                //cout << "planId: " << plan.id << endl;
                long long minOre = min(plan.clayRobotCostOre, plan.oreRobotCostOre);
                long long res = dfs(plan.id - 1, time - minOre, 1, 0, 0, 0, minOre, 0, 0, 0);
                //cout << "geode: " << res << endl;
                sumQuality2 *= res;
                unsigned long long end_time = clock();
                unsigned long long time = end_time - start_time;
                //cout << "time: " << time / 1000.0 << endl << endl;
            };
        }
        return sumQuality2;
    }
private:
    struct Plan {
        long long id, oreRobotCostOre, clayRobotCostOre, obsidianRobotCostOre, obsidianRobotCostClay, geodeRobotCostOre, geodeRobotCostObsidian;
        long long maxNeedOre, maxNeedClay, maxNeedObsidian, maxRes;
    };

    vector<Plan> plans;

    void getPlansFromFiles(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string str;
            Plan plan;
            iss >> str >> plan.id >> str;
            iss >> str >> str >> str >> str >> plan.oreRobotCostOre >> str;
            iss >> str >> str >> str >> str >> plan.clayRobotCostOre >> str;
            iss >> str >> str >> str >> str >> plan.obsidianRobotCostOre >> str >> str >> plan.obsidianRobotCostClay >> str;
            iss >> str >> str >> str >> str >> plan.geodeRobotCostOre >> str >> str >> plan.geodeRobotCostObsidian >> str;
            plan.maxNeedOre = max(max(plan.oreRobotCostOre, plan.clayRobotCostOre), max(plan.obsidianRobotCostOre, plan.geodeRobotCostOre)) + 1;
            plan.maxNeedClay = plan.obsidianRobotCostClay + 1;
            plan.maxNeedObsidian = plan.geodeRobotCostObsidian + 1;
            plan.maxRes = plan.oreRobotCostOre + plan.clayRobotCostOre + plan.obsidianRobotCostOre
                + plan.geodeRobotCostOre + plan.obsidianRobotCostClay + plan.geodeRobotCostObsidian;
            plans.push_back(plan);
        }
        inputFile.close();
    }

    void clearCache(Plan plan) {
        for (long long i = 0; i <= TIME_MAX; ++i) {
            cache[i].clear();
        }
    }
    long long dfs(long long id, long long time, long long oreRobotCount, long long clayRobotCount, long long obsidianRobotCount, long long geodeRobotCount, long long ore, long long clay, long long obsidian, long long geode) {
        if (time == 0) {
            return geode;
        }
        if (oreRobotCount > plans[id].maxNeedOre || clayRobotCount > plans[id].maxNeedClay || obsidianRobotCount > plans[id].maxNeedObsidian) {
            return 0;
        }
        if (ore >= plans[id].maxRes) {
            ore = plans[id].maxRes;
        }
        if (clay >= plans[id].maxRes) {
            clay = plans[id].maxRes;
        }
        if (obsidian >= plans[id].maxRes) {
            obsidian = plans[id].maxRes;
        }
        if (oreRobotCount == plans[id].maxNeedOre) {
            ore = plans[id].maxNeedOre;
        }
        if (clayRobotCount == plans[id].maxNeedClay) {
            clay = plans[id].maxNeedClay;
        }
        if (obsidianRobotCount == plans[id].maxNeedObsidian) {
            obsidian = plans[id].maxNeedObsidian;
        }
        State state = { ore, oreRobotCount, clay, clayRobotCount, obsidian, obsidianRobotCount, geodeRobotCount };
        if (cache[time].count(state)) {
            return cache[time][state];
        }
        long long& cur = cache[time][state];
        if (oreRobotCount == plans[id].geodeRobotCostOre && obsidianRobotCount == plans[id].geodeRobotCostObsidian) {
            if (ore != plans[id].geodeRobotCostOre && obsidian != plans[id].geodeRobotCostObsidian) {
                cur = 0;
            }
            else {
                cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount, geodeRobotCount + 1, ore + oreRobotCount - plans[id].geodeRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount - plans[id].geodeRobotCostObsidian, geode + geodeRobotCount));
            }
        }
        else {
            if (plans[id].oreRobotCostOre <= ore) {
                cur = max(cur, dfs(id, time - 1, oreRobotCount + 1, clayRobotCount, obsidianRobotCount, geodeRobotCount, ore + oreRobotCount - plans[id].oreRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount, geode + geodeRobotCount));
            }

            if (plans[id].clayRobotCostOre <= ore) {
                cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount + 1, obsidianRobotCount, geodeRobotCount, ore + oreRobotCount - plans[id].clayRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount, geode + geodeRobotCount));
            }

            if (plans[id].obsidianRobotCostOre <= ore && plans[id].obsidianRobotCostClay <= clay) {
                cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount + 1, geodeRobotCount, ore + oreRobotCount - plans[id].obsidianRobotCostOre, clay + clayRobotCount - plans[id].obsidianRobotCostClay, obsidian + obsidianRobotCount, geode + geodeRobotCount));
            }

            if (plans[id].geodeRobotCostOre <= ore && plans[id].geodeRobotCostObsidian <= obsidian) {
                cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount, geodeRobotCount + 1, ore + oreRobotCount - plans[id].geodeRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount - plans[id].geodeRobotCostObsidian, geode + geodeRobotCount));
            }

            if (ore <= plans[id].maxRes && clay <= plans[id].maxRes && obsidian <= plans[id].maxRes) {
                cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount, geodeRobotCount, ore + oreRobotCount, clay + clayRobotCount, obsidian + obsidianRobotCount, geode + geodeRobotCount));
            }
        }

        return cur;
    }
};

void day19_start(string filename) {
    cout << endl << "Day 19" << endl;
    NotEnoughMinerals notEnoughMinerals(filename);
    // todo: �������� ��� ��������������
    cout << "part 1: " << notEnoughMinerals.getSumQuality(24) << endl;
    cout << "part 2: " << notEnoughMinerals.getSumQuality2(32) << endl;
}