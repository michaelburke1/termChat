// Final Project
/* Michael O'Malley
   Michael Burke
   Billy Theisen 
   
This file is the same as Log.cpp except it does not include the boost.python
module, and an additional function called test(int) is included. This file 
and the test(int) function is used to benchmark and test the backend
   
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <time.h>
#include <chrono> 
#include <iomanip>

#define TABLE_SIZE 1024
#define LOAD_FACTOR .95

typedef std::chrono::high_resolution_clock  Clock; 

using namespace std;
 
struct User {

    string ipAddress;
    int numOfMessages;
    int startTime;
    int lastMessage;

};

class Log {

    public:
        Log();
        ~Log();
        void insertTime(time_t, string, string);
        void insertName(time_t, string, string);
        vector<pair<string, string> > searchTime(int);
        void resizeTime(int);
        void test(int);
        void printTimeRange(int, int);
        void printTimeRangeByName(int, int, string);
        void printByName(string);
        bool addUser(string, string);
        time_t localToTime(struct tm);
        void timeToLocal(time_t);

        typedef map<time_t, vector<pair<string, string> > > myMap;
        typedef vector<pair<time_t, string> > myVec;

        myMap *logByTime;
        int tSizeTime;
        float nMessages, loadFactor;
        map<string, myVec> UserName;
        map<string, string> userToIpAddress;

};

Log:: Log() {

    logByTime = nullptr;
    tSizeTime = TABLE_SIZE;
    nMessages = 0;
    loadFactor = 0;

    resizeTime(tSizeTime);
}

Log:: ~Log() {
    delete [] logByTime;
}

void Log:: insertTime(time_t key, string name, string value) {
    nMessages++;
    int bucket;
    bucket = key % tSizeTime;
	
    logByTime[bucket][key].push_back(pair<string, string>{name, value});
    loadFactor = nMessages / tSizeTime;
    if (loadFactor >= LOAD_FACTOR) {
        resizeTime(2*tSizeTime);
    }
}

void Log:: insertName(time_t secs, string name, string value) {
    UserName[name].push_back(pair<time_t, string>{secs, value});
}

vector<pair<string, string> > Log:: searchTime(int key) {
    int bucket;
    bucket = key % tSizeTime;
    return logByTime[bucket][key];
}

void Log:: resizeTime(int new_size) {
    if (!logByTime) {
        logByTime = new myMap [new_size];
        return;
    }

    myMap *newLog = new myMap [new_size];
    myMap *oldLog = logByTime;
    
    logByTime = newLog;
    int oldSize = tSizeTime;
    tSizeTime = new_size;
   
    nMessages = 0;
    for (int i = 0; i < oldSize; i++) {
        for (auto it: oldLog[i]) {
            for (int j = 0; j < it.second.size(); j++) {
                insertTime(it.first, it.second[j].first, it.second[j].second);
            }           
        }
    }
    delete [] oldLog;
}

void Log:: test(int input) {
    // input determines if we want to also test the search
    // input = 1 if we want to test insert and search
    // input = 0 if we just want to test insert
    time_t i = 0;
    string j;
    string k;
    string message = "";
    string line;
    int count0 = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> i;            // parses the time
        ss >> j;            // parses username
        message = "";       // parses message
        ss >> message;
        while (ss >> k) {
            message += " ";
            message += k;
        }
        // add user 
        addUser(j, to_string(rand() % 100000));
        // count number of messages
        count0++;
        cout << i << " " << j << "\t" << message << endl;
        insertName(i, j, message); // insert based on name
        insertTime(i, j, message); // insert into hash table based on time
    }
    if (input) {
        auto search_start = Clock::now();
        for (int i = 0; i < count0; i++) {
            searchTime(i);
        }
        cout << count0 << " count " << endl;
        auto search_stop  = Clock::now();
        auto search_diff  = search_stop - search_start;

        std::cout << std::setprecision(5);
        std::cout << std::chrono::duration<double>(search_diff).count(); 
        cout << " s     |" << std::endl;
    }
}

void Log:: printTimeRange(int start, int end) {
    int curr = start;
    while (curr != end + 1) {
        auto it = searchTime(curr);
        for (int i = 0; i < it.size(); i++) {
            timeToLocal(curr);
            cout << it[i].first << " said " << it[i].second << endl;
        }
        curr++;
    }
}

void Log:: printTimeRangeByName(int start, int end, string name) {
    for (int i = 0; i < UserName[name].size(); i++) {
        if (UserName[name][i].first >= start && UserName[name][i].first <= end) {
            timeToLocal(UserName[name][i].first);
            cout << name << " said " << UserName[name][i].second << endl; 
        }
    }
}

void Log:: printByName(string name) {
    for (int i = 0; i < UserName[name].size(); i++) {
        timeToLocal(UserName[name][i].first);
        cout << name << " said " << UserName[name][i].second << endl;
    }
}

bool Log:: addUser(string userName, string ipAddress) {

    auto it = userToIpAddress.find(userName);
    
    if (it != userToIpAddress.end()) {
        return false;
    }

    for (auto it: userToIpAddress) {
        if (it.second == ipAddress) {
            return false;
        }
    }
    userToIpAddress[userName] = ipAddress;
    return true;
}

time_t Log:: localToTime(struct tm t) {
    return mktime(&t);
}

void Log:: timeToLocal(time_t secs) {
    struct tm * timeinfo;
    timeinfo = localtime (&secs);
    cout << "Time: " << asctime(timeinfo); 
}

// Main Execution


int main(int argc, char *argv[]) {
    if (argc == 2) {
        Log log;
        log.test(1);
    } else {
        Log log;
        log.test(0);
    }
    return EXIT_SUCCESS;
}

// vim: set sts=:4 sw=4 ts=8 expandtab ft=cpp:
