#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>
#include <string.h>

using namespace std;
#define VERTEX_COUNT 50
#define MAX_TIME 30
#define MAX_VIS 100000
#define INF_DISTANCE 1e5

int localCache[VERTEX_COUNT][MAX_TIME][MAX_VIS];

class ProboscideaVolcanium {
    public:
        ProboscideaVolcanium(string filename) {
            readData(filename);
            generateGraph();
        }
        
        int getMaxPreccision(string startVertexName = "AA", int remainingTime = MAX_TIME, bool needElephantHelp = false) {
            int startVertex = flowsValveId[valveId[startVertexName]];
            memset(localCache, -1, sizeof localCache);
            if (!needElephantHelp) {
                return dfs(startVertex, remainingTime - 1, 0);
            }
            int N = interest.size();
            int all = (1 << N) - 1;
            int workWithElephant = 0;
            for (int msk = 0; msk < all; ++msk) {
                int myWork = dfs(startVertex, remainingTime - 1, msk);
                int elephantWork = dfs(startVertex, remainingTime - 1, all - msk);
                workWithElephant = max(workWithElephant, myWork + elephantWork);
            }
            return workWithElephant;
        }
    private:
        struct Edge {
            int to, w;
        };
        vector<vector<int>> graph;
        vector<vector<Edge>> edges;
        map<string, int> valveId;
        vector<int> flowsValveId, flows;
        set<int> interest;
        void readData(string filename) {
            ifstream inputFile(filename);
            int flowsValveNumber = 0, valveNumber = 0;
            string line;
            graph.resize(VERTEX_COUNT);
            flowsValveId.resize(VERTEX_COUNT);
            while (getline(inputFile, line)) {
                istringstream iss(line);
                string buf;
                string currentValve;
                int flowRate;
                char ch;
                iss >> buf >> currentValve >> buf >> buf;
                iss >> ch >> ch >> ch >> ch >> ch >> flowRate >> ch;
                iss >> buf >> buf >> buf >> buf;
                if (!valveId.count(currentValve)) {
                    valveId[currentValve] = valveNumber++;
                }
                while (true) {
                    string to = "";
                    iss >> ch;
                    to += ch;
                    iss >> ch;
                    to += ch;
                    if (!valveId.count(to)) {
                        valveId[to] = valveNumber++;
                    }
                    graph[valveId[currentValve]].push_back(valveId[to]);
                    if (!(iss >> ch)) {
                        break;
                    }
                }
                if (flowRate || currentValve == "AA") {
                    interest.insert(valveId[currentValve]);
                    flows.push_back(flowRate);
                    flowsValveId[valveId[currentValve]] = flowsValveNumber++;
                }
            }
            inputFile.close();
        }
        void generateGraph() {
            edges.resize(VERTEX_COUNT);
            for (int src : interest) {
                vector<int> dist(VERTEX_COUNT, INF_DISTANCE);
                vector<int> q;
                q.push_back(src);
                dist[src] = 0;
                while (!q.empty()) {
                    int v = q.front();
                    q.erase(q.begin());
                    for (int to : graph[v]) {
                        if (dist[to] == INF_DISTANCE) {
                            dist[to] = dist[v] + 1;
                            if (interest.count(to)) {
                                edges[flowsValveId[src]].push_back({ flowsValveId[to], dist[to] });
                            }
                            q.push_back(to);
                        }
                    }
                }
            }
        }

        int dfs(int vertex, int time, int vis) {
            if (time == -1) {
                return 0;
            }
            if (localCache[vertex][time][vis] != -1) {
                return localCache[vertex][time][vis];
            }
            int& ans = localCache[vertex][time][vis];
            ans = 0;
            for (auto e : edges[vertex]) {
                if (e.w > time || 1 & (vis >> e.to)) {
                    continue;
                }
                int cont = dfs(e.to, time - e.w - 1, vis + (1 << e.to));
                ans = max(ans, cont + (time - e.w) * flows[e.to]);
            }
            return ans;
        }
};

void day16_start(string filename) {
    cout << endl << "Day 16" << endl;
    ProboscideaVolcanium volcanium(filename);
    cout << "part 1: " << volcanium.getMaxPreccision() << endl;
    cout << "part 2: " << volcanium.getMaxPreccision("AA", 26, true) << endl;
}
