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

vector<string> split(const string& s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void replace_all(
    string& s,
    string const& toReplace,
    string const& replaceWith
) {
    string buf;
    size_t pos = 0;
    size_t prevPos;

    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}

void printAnswer(list<char>* board, int size) {
    for (int i = 1; i < size; i++) {
        cout << board[i].back();
    }
    cout << endl;
}

void day5_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
    }

    int part1{ 0 }, part2{ 0 };
    vector<string> stacksInfo;
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        if (line.empty()) {
            break;
        }
        stacksInfo.push_back(line);
    }
    string rooms = stacksInfo.back();
    replace_all(rooms, "   ", "-");
    vector<string> elems = split(rooms, '-');
    const int length = elems.size() + 1;
    list<char> *board1, *board2;
    board1 = new list<char>[length];
    board2 = new list<char>[length];
    for (int i = stacksInfo.size() - 2; i >= 0; i--) {
        string level = stacksInfo[i];
        replace_all(level, "    ", "[0] ");
        replace_all(level, "][", "] [");
        replace_all(level, "  ", " ");
        vector<string> containers = split(level, ' ');
        for (int j = 0; j < containers.size(); j++) {
            if (containers[j] != "[0]") {
                board1[j + 1].push_back(containers[j][1]);
                board2[j + 1].push_back(containers[j][1]);
            }
        }
    }

    while (!inputFile.eof()) {
        string musor;
        int count = 0, from = 0, to = 0;
        inputFile >> musor >> count >> musor >> from >> musor >> to;
        if (count == 0 || from == 0 || to == 0) {
            break;
        }
        list<char> temp;
        for (int i = 0; i < count; i++) {
           char container = board2[from].back();
           board2[from].pop_back();
           temp.push_back(container);
        }
        for (int i = 0; i < count; i++) {
           char container2 = temp.back();
           temp.pop_back();
           board2[to].push_back(container2);

           char container = board1[from].back();
           board1[from].pop_back();
           board1[to].push_back(container);
        }
    }

    cout << endl << "Day 5" << endl;
    cout << "part 1: ";
    printAnswer(board1, length);
    cout << "part 2: ";
    printAnswer(board2, length);

    inputFile.close();
}
