#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;
class MonkeyMath {
public:
    const string ROOT_MONKEY_NAME = "root";
    MonkeyMath(string filename) {
        getMonkeyJobFromFile(filename);
    }
    long long getCompliteOperationValue(string monkeyName) {
        auto& monkeyJob = monkeyDictionary[monkeyName];
        if (monkeyName == HUMAN_NAME) {
            monkeyJob.humanValueUse = true;
        }
        if (!monkeyJob.operationComplite) {
            long long monkeyJobValue1 = getCompliteOperationValue(monkeyJob.monkey1);
            long long monkeyJobValue2 = getCompliteOperationValue(monkeyJob.monkey2);
            long long jobValue = monkeyJobValue1;
            switch (monkeyJob.operation) {
            case '+':
                jobValue += monkeyJobValue2;
                break;
            case '-':
                jobValue -= monkeyJobValue2;
                break;
            case '/':
                jobValue /= monkeyJobValue2;
                break;
            case '*':
                jobValue *= monkeyJobValue2;
                break;
            }
            monkeyJob.jobValue = jobValue;
            monkeyJob.operationComplite = true;
            if (monkeyDictionary[monkeyJob.monkey1].humanValueUse || monkeyDictionary[monkeyJob.monkey2].humanValueUse) {
                monkeyJob.humanValueUse = true;
            }
        }
        return monkeyJob.jobValue;
    }
    long long gethumanValueForRootEqual() {
        auto& humanJob = monkeyDictionary[HUMAN_NAME];
        auto& rootJob = monkeyDictionary[ROOT_MONKEY_NAME];

        long long unsigned oldDif = (long long unsigned)abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue);
        long long sign = 1;
        long long slag = 1000000000LL;
        long long oldValue;
        //long long slag = 1LL;

        while (monkeyDictionary[rootJob.monkey1].jobValue != monkeyDictionary[rootJob.monkey2].jobValue) {
            //cout << "olf = " << oldDif - abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue)  << endl;
            if (oldDif < (long long unsigned)abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue)) {
                sign *= -1;
                slag /= 2;
                if (slag == 0) {
                    slag = 1;
                }
            }
            oldDif = (long long unsigned) abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue);
            humanJob.jobValue += sign * slag;
            clearHumanUsage();
            monkeyDictionary[HUMAN_NAME] = humanJob;
            getCompliteOperationValue(rootJob.monkey1);
            getCompliteOperationValue(rootJob.monkey2);
            //cout << "human = " << humanJob.jobValue << endl;
            //cout << "dif = " << abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue) << "  human = " << humanJob.jobValue << endl;

        }
        while (monkeyDictionary[rootJob.monkey1].jobValue == monkeyDictionary[rootJob.monkey2].jobValue) {
            //cout << "olf = " << oldDif - abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue)  << endl;
            if (oldDif < (long long unsigned)abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue)) {
                sign *= -1;
                slag /= 2;
                if (slag == 0) {
                    slag = 1;
                }
            }
            oldDif = (long long unsigned) abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue);
            humanJob.jobValue += sign;
            clearHumanUsage();
            monkeyDictionary[HUMAN_NAME] = humanJob;
            getCompliteOperationValue(rootJob.monkey1);
            getCompliteOperationValue(rootJob.monkey2);
            //cout << "human = " << humanJob.jobValue << endl;
            //cout << "dif = " << abs(monkeyDictionary[rootJob.monkey1].jobValue - monkeyDictionary[rootJob.monkey2].jobValue) << "  human = " << humanJob.jobValue << endl;

        }
        humanJob.jobValue += -sign;
        clearHumanUsage();
        long long val1 = getCompliteOperationValue(rootJob.monkey1);
        long long val2 = getCompliteOperationValue(rootJob.monkey2);
        //cout << "val1 = " << val1 << endl;
        //cout << "val2 = " << val2 << endl;
        return humanJob.jobValue;
    }
private:
    const string HUMAN_NAME = "humn";
    struct MonkeyJob {
        long long jobValue;
        char operation;
        string monkey1;
        string monkey2;
        bool operationComplite = false;
        bool humanValueUse = false;
    };
    map<string, MonkeyJob> monkeyDictionary;
    void clearHumanUsage() {
        for (auto& el : monkeyDictionary) {
            if (el.second.humanValueUse) {
                if (el.second.monkey1 != "") {
                    el.second.operationComplite = false;
                }
            }
        }
    }
    void getMonkeyJobFromFile(string filename) {
        ifstream inputFile(filename);
        string line;

        while (getline(inputFile, line)) {
            if (line.empty()) {
                break;
            }
            istringstream iss(line);
            string monkeyName;
            iss >> monkeyName;
            monkeyName = monkeyName.substr(0, 4);
            MonkeyJob monkeyJob;
            if (line[6] >= '0' && line[6] <= '9') {
                iss >> monkeyJob.jobValue;
                monkeyJob.operationComplite = true;
            }
            else {
                iss >> monkeyJob.monkey1 >> monkeyJob.operation >> monkeyJob.monkey2;
            }
            monkeyDictionary[monkeyName] = monkeyJob;
        }
        inputFile.close();
    }
};
void day21_start(string filename) {
    cout << endl << "Day 21" << endl;
    MonkeyMath monkeyMath(filename);
    cout << "part 1: " << monkeyMath.getCompliteOperationValue(monkeyMath.ROOT_MONKEY_NAME) << endl;
    // todo: подумать над оптимизацией
    cout << "part 2: " << monkeyMath.gethumanValueForRootEqual() << endl;

}