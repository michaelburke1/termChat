12/9/2016
Michael O'Malley
Michael Burke
Billy Theisen

Data Structures Final Project
=============================

File Descriptions:

	bench-test-insert.sh	- tests log insert function
	bench-test-search.sh  	- tests log search function
	chatClient.py         	- client connection script
	chatServer.py         	- server connection script
	CONTRIBUTORS.md     	- lists contributions
	createMessages.cpp  	- test script, creates specific
							  amount of random messages
	Log.cpp             	- hash table implementation
	Log.so              	- python library to wrap c++
	LogTest.cpp  			- Log implementation without
							  python for testing
	Makefile     			- compiles necessary files
							  and creates executables
	measure.cpp				- outsourced script to measure
							  time and memory

Python Setup:

The python set up is extremely similar to how we did the simple echo server
in unix. One difference is that the server now has a list of sockets, which
represent the connected clients. The client now must all listen to the server
in order to be able to recieve the messages from others. Everytime a message
is pushed to the server from a client, the server stores it in the chat log,
and then pushes the message to all the other clients which are always listening
for new data from the server in a while loop. This unfortunalely leads to a
problem of new data from the server overwriting data the the client is currently
writing, but has not yet pushed.

Running Instructions:

In order to begin the chat, the following command has to be used:
		python ./chatClient.py [IP address] [Port]
Then follow the prompts to enter username. When another user connects
to the same server, a chat room is opened and chatting can happen
between terminals. This is all that needs to be done to communicate.

Test Suite:

The test suit is included in the Makefile and it runs with the command
make test after make bench-test has been run (for the script executables).
Just like in our challenges, it tests output, time, and
memory. It creates a random input of 1000 messages to enter into the
table. The output for username, time, and message are checked. Time
over 1 second is not acceptable. And the memory check is for memory
leaks. This is all done on the LogTest executable, which is the
implementation of our hash table without the python code.

Shell Script Analysis Results:

In order to compile the test files, all that needs to be done
on the command line is make bench-test. This will make the executables
and run the shell bench test scripts. Insert test simply checks
the time the program takes to run after inserting different amounts
of messages. Search has to first insert everything, then after
that, the search function within the hash table class is timed.
It does not output a memory, however we know that it will have the
same memory as the input test, so we copied it over.

./bench-test-insert.sh
| Number of Messages | Insert Time      | Memory Use       |
|--------------------|------------------|------------------|
| 10                 | 0.001998 secs    | 1.273438 Mbytes  |
| 100                | 0.001999 secs    | 1.296875 Mbytes  |
| 1000               | 0.010998 secs    | 1.714844 Mbytes  |
| 10000              | 0.107982 secs    | 6.625000 Mbytes  |
| 100000             | 1.000847 secs    | 50.312500 Mbytes |
| 1000000            | 11.909189 secs   | 646.796875 Mbytes|

./bench-test-search.sh
| Number of Messages | Search Time      | Memory Use       |
|--------------------|------------------|------------------|
| 10                 | 4.6714e-05 s     | 1.273438 Mbytes  |
| 100                | 0.00015524 s     | 1.296875 Mbytes  |
| 1000               | 0.00052199 s     | 1.714844 Mbytes  |
| 10000              | 0.0055032 s     	| 6.625000 Mbytes  |
| 100000             | 0.058396 s     	| 50.312500 Mbytes |
| 1000000            | 0.55518 s   		| 646.796875 Mbytes|


