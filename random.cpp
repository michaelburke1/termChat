#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

string a [] = {"Bob", "Mike", "Joe", "Kate", "Jose", "Julie"};
string b [] = {"how are ya",
                 "Hi Mike!",
                 "Kate is so cool", 
                 "My name is Mike",
                "Hi Mike my name is Jose", 
                "Hi Bob I am Jose", 
                "Hi Jose I am Mike",
                "Joe, you are so annoying", 
                "wait, hes not annoying, I am!",
                "Kate is good at chess", 
                "*sneeze*", 
                "I like your personality", 
                "Why does my cat eat so much?",
                "Bob works at a high school", 
                "I'm not that fast, but I can jump high",
                "Wait, what is today's date?", 
                "Well, goodbye"};

// this file generates sample messages to test the backend of LogTest.cpp
// array a is an array of random names
// array b is an array of random messages
// The file takes two parameters, time and number of messages. 
// default the time to 72000 

int main(int argc, char *argv[]) {

    /*std::istringstream iss( argv[1] );
    std::istringstream iss1( argv[2] );
    long long time0;
    iss >> time0;
    long long messages;
    iss1 >> messages;
    for (long long i = 0; i < messages; i++) { 
        cout << i;
        cout << " " << a[rand() % 6] << " " << b[rand() % 17] << endl; 
    }*/

    while (1) {
        string stuff;
        cin >> stuff;
        cout << rand() % 10 + 1 << endl;
    }


}
