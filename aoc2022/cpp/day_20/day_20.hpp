#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class GrovePositioningSystem {
public:
    GrovePositioningSystem(string filename) {
        getEncryptedFile(filename);
    }
    long long getGroveSum(int encuredCountCycle = 1, bool useDecryptionKey = false) {
        shafle = encreptedFile;
        for (int i = 0; i < encuredCountCycle; i++) {
            encrepted(useDecryptionKey);
            //cout << "cycle: " << i + 1 << endl;
            //displayEncryptedFile(useDecryptionKey);
        }

        long long sum = 0;
        sum = getValueAfterZero(1000) + getValueAfterZero(2000) + getValueAfterZero(3000);
        if (useDecryptionKey) {
            sum *= decryptionKey;
        }
        //displayEncryptedFile();
        return sum;
    }
private:
    vector<pair<long long, int>> encreptedFile;
    vector<pair<long long, int>> shafle;

    long long decryptionKey = 811589153LL;
    long long getValueAfterZero(int offset) {
        auto iter = shafle.cbegin();
        int pos = 0;
        while ((*iter).first != 0) {
            iter++;
            pos++;
        }
        int newPos = (pos + offset) % shafle.size();
        long long value = shafle[newPos].first;
        return value;
    }

    void getEncryptedFile(string filename) {
        ifstream inputFile(filename);
        string line;
        int index = 0;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            int number;
            iss >> number;
            pair<long long, int> el;
            el.first = number;
            el.second = index++;
            encreptedFile.push_back(el);
        }
        inputFile.close();
    }

    void encrepted(bool useDecryptionKey = false) {
        int stepCounts = encreptedFile.size();
        for (int i = 0; i < stepCounts; i++) {
            int pos = 0;
            for (int j = 0; j < stepCounts; j++) {
                if (shafle[j].second == encreptedFile[i].second) {
                    pos = j;
                    break;
                }
            }
            shafle.erase(shafle.cbegin() + pos);

            auto element = encreptedFile[i];
            long long newPos = element.first;
            if (useDecryptionKey) {
                newPos *= (decryptionKey % shafle.size());
            }
            while (newPos < 0) {
                newPos += shafle.size();
            }
            newPos += pos;
            newPos %= shafle.size();
            
            if (newPos == 0) {
                newPos = shafle.size();
            }
            shafle.insert(shafle.cbegin() + newPos, element);

            //cout << "step: " << i + 1 << endl;
            //displayEncryptedFile(useDecryptionKey);
        }
    }
    void displayEncryptedFile(bool useDecryptionKey = false) {
        for (auto element : shafle) {
            cout << element.first * (useDecryptionKey ? decryptionKey : 1) << " ";
        }
        cout << endl;
    }
};

void day20_start(string filename) {
    cout << endl << "Day 20" << endl;
    GrovePositioningSystem grovePositioningSystem(filename);
    cout << "part 1: "  << grovePositioningSystem.getGroveSum() << endl;
    // todo: подумать над оптимизацией
    cout << "part 2: "  << grovePositioningSystem.getGroveSum(10, true) << endl;
}