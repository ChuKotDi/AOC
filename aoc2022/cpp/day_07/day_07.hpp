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

vector<string> splitCommand(const string& s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

struct tnode {
    string name = "\\";
    long size = 0;
    struct tnode* parent;
    struct vector<tnode*> childs;
};

struct tnode* addnode(string name, tnode* parent) {
    tnode* node = NULL;
    if (parent != NULL) {
        for (int i = 0; i < parent->childs.size(); i++) {
            tnode* child = parent->childs[i];
            if (child->name == name) {
                node = child;
            }
        }
    }
    if (node == NULL) {
        node = new tnode;
        node->name = name;
        node->parent = parent;
        if (parent != NULL) {
            parent->childs.push_back(node);
        }
    }

    return node;
}

void freemem(tnode* tree) {
    if (tree != NULL) {
        for (int i = 0; i < tree->childs.size(); i++) {
            freemem(tree->childs[i]);
        }
        delete tree;
    }
}

vector<long> sizes;

long getSize(tnode* tree) {
    long size = 0;
    size += tree->size;
    for (int i = 0; i < tree->childs.size(); i++) {
        size += getSize(tree->childs[i]);
    }
    sizes.push_back(size);
    return size;
}

void day7_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    vector<string> commands;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        if (line.empty()) {
            break;
        }
        commands.push_back(line);
    }

    tnode* tree = NULL;
    tnode* parent = NULL;
    string dirname = "\\";
    for (int i = 0; i < commands.size(); i++) {
        string command = commands[i];
        if (command[0] == '$') {
            if (command == "$ ls") {
                bool work = true;
                while (work) {
                    i++;
                    if (i < commands.size()) {
                        command = commands[i];
                        if (command[0] == '$') {
                            work = false;
                            i--;
                        }
                        else if (command[0] == 'd') {
                            vector<string> parts = splitCommand(command, ' ');
                            dirname = parts.back();
                            addnode(dirname, tree);
                        }
                        else {
                            vector<string> parts = splitCommand(command, ' ');
                            long size = stol(parts[0]);;
                            if (tree != NULL) {
                                tree->size += size;
                            }
                        }
                    }
                    else {
                        work = false;
                    }
                }
            }
            else if (command == "$ cd ..") {
                if (tree != NULL && tree->parent != NULL) {
                    tree = tree->parent;
                }
            }
            else {
                vector<string> parts =  splitCommand(command, ' ');
                dirname = parts.back();
                tree = addnode(dirname, tree);
                if (parent == NULL) {
                    parent = tree;
                }
            }
        }
    }

    long allSize = getSize(parent);
    part1 = 0;
    long maxSizeForPart1 = 100000;
    long needFreeSizeForPart2 = 30000000;
    long maxDiskSize = 70000000;
    long freeSpace = maxDiskSize - allSize;
    long needSpace = needFreeSizeForPart2 - freeSpace;
    part2 = allSize;
    for (int i = 0; i < sizes.size(); i++) {
        if (sizes[i] < maxSizeForPart1) {
            part1 += sizes[i];
        }
        if (sizes[i] > needSpace && sizes[i] < part2) {
            part2 = sizes[i];
        }
    }

    freemem(tree);
    cout << endl << "Day 7" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;

    inputFile.close();
}
