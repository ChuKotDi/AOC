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

class Graph
{
    int numVertices = -1;
    list<int>* adjLists = NULL;
    bool* visited = NULL;
    int* parentForMinPath = NULL;
public:
    Graph(int vertices)
    {
        numVertices = vertices;
        adjLists = new list<int>[vertices];
        parentForMinPath = new int[numVertices];
        visited = new bool[numVertices];
    }

    void addEdge(int src, int dest)
    {
        //adjLists[src].push_back(dest);
        adjLists[dest].push_back(src);
    }

    void BFS(int startVertex)
    {
        free(parentForMinPath);
        free(visited);
        parentForMinPath = new int[numVertices];
        visited = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
            parentForMinPath[i] = -1;
        }
        list<int> queue;

        visited[startVertex] = true;
        queue.push_back(startVertex);

        list<int>::iterator i;

        while (!queue.empty())
        {
            int currVertex = queue.front();
            queue.pop_front();

            for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
            {
                int adjVertex = *i;
                if (!visited[adjVertex])
                {
                    visited[adjVertex] = true;
                    parentForMinPath[adjVertex] = currVertex;
                    queue.push_back(adjVertex);
                }
            }
        }
    }
    
    vector<int> getMinPathFromBFS(int endVertex, int startVertex) {
        vector<int> minPath;
        if (parentForMinPath != NULL && endVertex <= numVertices && endVertex != -1 && startVertex != -1 && startVertex <= numVertices) {
            int curVertex = endVertex;
            while (curVertex != startVertex) {
                minPath.push_back(curVertex);
                curVertex = parentForMinPath[curVertex];

                bool circle = false;
                for (int i = 0; i < minPath.size(); i++) {
                    if (curVertex == minPath[i] || curVertex == -1) {
                        circle = true;
                    }
                }
                if (circle) {
                    minPath.clear();
                    break;
                }
            }
        }
        return minPath;
    }
};

void day12_start(string filename) {
    cout << endl << "Day 12" << endl;
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл потерялся оО" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    int monkeyNumber = 0;
    vector<string> stringMap;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);

        if (!line.empty()) {
            stringMap.push_back(line);
        }
        else {
            break;
        }
    }
    int vertexCount = stringMap.size() * stringMap[0].size();
    Graph g(vertexCount);
    int startVertex = -1;
    int endVertex = -1;
    vector<vector<int>> heightMap;
    vector<int> a_index;
    for (int y = 0; y < stringMap.size(); y++) {
        vector<int> heightline;
        for (int x = 0; x < stringMap[y].size(); x++) {
            int curVertex = y * stringMap[0].size() + x;
            int height = (int)stringMap[y][x];
            if (stringMap[y][x] == 'S') {
                startVertex = curVertex;
                height = (int)'a';
            }
            if (stringMap[y][x] == 'E') {
                endVertex = curVertex;
                height = (int)'z';
            }
            if (stringMap[y][x] == 'S' || stringMap[y][x] == 'a') {
                a_index.push_back(curVertex);
            }
            heightline.push_back(height);
        }
        heightMap.push_back(heightline);
    }

    for (int y = 0; y < heightMap.size(); y++) {
        for (int x = 0; x < heightMap[y].size(); x++) {
            int curVertex = y * heightMap[y].size() + x;
            int vertexIndex = -1;
            if (x - 1 >= 0 && (abs(heightMap[y][x - 1] - heightMap[y][x]) <= 1 || heightMap[y][x - 1] - heightMap[y][x] < 0)) {
                vertexIndex = y * heightMap[y].size() + x - 1;
                g.addEdge(curVertex, vertexIndex);
            }
            if (x + 1 < heightMap[y].size() && (abs(heightMap[y][x + 1] - heightMap[y][x]) <= 1 || heightMap[y][x + 1] - heightMap[y][x] < 0)) {
                vertexIndex = y * heightMap[y].size() + x + 1;
                g.addEdge(curVertex, vertexIndex);
            }
            if (y - 1 >= 0 && (abs(heightMap[y - 1][x] - heightMap[y][x]) <= 1 || heightMap[y - 1][x] - heightMap[y][x] < 0)) {
                vertexIndex = (y - 1) * heightMap[y].size() + x;
                g.addEdge(curVertex, vertexIndex);
            }
            if (y + 1 < heightMap.size() && (abs(heightMap[y + 1][x] - heightMap[y][x]) <= 1 || heightMap[y + 1][x] - heightMap[y][x] < 0)) {
                vertexIndex = (y + 1) * heightMap[y].size() + x;
                g.addEdge(curVertex, vertexIndex);
            }
        }
    }

    g.BFS(endVertex);
    vector<int> path = g.getMinPathFromBFS(startVertex, endVertex);
    part1 = path.size();

    part2 = part1;
    for (int i = 0; i < a_index.size(); i++) {
        //g.BFS(a_index[i]);
        path = g.getMinPathFromBFS(a_index[i], endVertex);
        if (path.size() < part2 && path.size() != 0) {
            part2 = path.size();
        }
    }

    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
