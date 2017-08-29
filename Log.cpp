// Final Project
/* Michael O'Malley
   Michael Burke
   Billy Theisen */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <time.h>
#include <boost/python.hpp>


#define TABLE_SIZE 1024
#define LOAD_FACTOR .9


using namespace std;
namespace python = boost::python;
 
class Log {

    public:
        Log();
        ~Log();
        void insertTime(time_t, string, string);
        void insertName(time_t, string, string);
        vector<pair<string, string> > searchTime(int);
        void resizeTime(int);
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
// the constructor initializes the hash table
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
    // this insert refers to the hash table that sorts by message time sent
    nMessages++;        // incremements # of messages
    int bucket;
    // hash the value
    bucket = key % tSizeTime;

    // insert the value
    logByTime[bucket][key].push_back(pair<string, string>{name, value});
    // determine if we need to resize
    loadFactor = nMessages / tSizeTime; 
    if (loadFactor >= LOAD_FACTOR) {
        resizeTime(2*tSizeTime);
    }
}

void Log:: insertName(time_t secs, string name, string value) {
    // this insert refers to the map that stores each message based on userName
    UserName[name].push_back(pair<time_t, string>{secs, value});
}

vector<pair<string, string> > Log:: searchTime(int key) {
    int bucket;
    bucket = key % tSizeTime;
    return logByTime[bucket][key];
}

void Log:: resizeTime(int new_size) {
    // resize from project 4
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
}

void Log:: printTimeRange(int start, int end) {
    // prints all messages within two times
    // the times are given in epoch time in seconds
    // the print iterates through all the seconds between the two times,
    // searches to see if any messages exist for that time, and prints it if so
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
    // this print is like the one about but it further restricts it
    // to user name only in that time frame
    for (int i = 0; i < UserName[name].size(); i++) {
        if (UserName[name][i].first >= start && UserName[name][i].first <= end) {
            timeToLocal(UserName[name][i].first);
            cout << name << " said " << UserName[name][i].second << endl; 
        }
    }
}

void Log:: printByName(string name) {
    // prints all messages by a certain name
    for (int i = 0; i < UserName[name].size(); i++) {
        timeToLocal(UserName[name][i].first);
        cout << name << " said " << UserName[name][i].second << endl;
    }
}

bool Log:: addUser(string userName, string ipAddress) {
    // adds a user and their ipAddress 
    auto it = userToIpAddress.find(userName);
    // if username is already taken, return false
    if (it != userToIpAddress.end()) {
        return false;
    }
    // if ipAddress is already used, return false
    for (auto it: userToIpAddress) {
        if (it.second == ipAddress) { 
            return false;
        }
    }
    userToIpAddress[userName] = ipAddress;
    return true;
}

time_t Log:: localToTime(struct tm t) {
    // takes a struct of epoch time and converts into seconds
    return mktime(&t);
}

void Log:: timeToLocal(time_t secs) {
    // takes a time in seconds and converts it into a human readable time
    struct tm * timeinfo;
    timeinfo = localtime (&secs);
    cout << "Time: " << asctime(timeinfo); 
}

// python wrapping
// these allow the server to use the functions of Log.cpp

BOOST_PYTHON_MODULE(Log) {

    python::class_<Log>("Log")
        .def("insertTime", &Log::insertTime)
        .def("insertName", &Log::insertName)
        .def("searchTime", &Log::searchTime)
        .def("resizeTime", &Log::resizeTime)
        .def("printTimeRange", &Log::printTimeRange)
        .def("printByName", &Log::printByName)
        .def("addUser", &Log::addUser)
        .def("localToTime", &Log::localToTime)
        .def("timeToLocal", &Log::timeToLocal)
    ;
}

// Main Execution
// has no main execution. Only used in python on server

int main(int argc, char *argv[]) {
    return EXIT_SUCCESS;
}

// vim: set sts=:4 sw=4 ts=8 expandtab ft=cpp:
