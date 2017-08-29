PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
# compile mesh classes
TARGET = Log
#$(TARGET).so: $(TARGET).o
MEASURE=	test/measure

Linux:	Linux1 Linux0

Linux0:	$(TARGET).o
	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
#$(TARGET).o: $(TARGET).cpp
Linux1:	$(TARGET).cpp
	g++ -std=c++11 -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp

mac: Log.cpp
	g++ -std=c++11 -I/usr/local/opt/boost155/include -I/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/ -fpic -c -o Log.o Log.cpp
	g++ -o Log.so -shared Log.o -lpython2.7 /usr/local/Cellar/boost-python/1.60.0/lib/libboost_python.a

bench-test: createMessages.cpp LogTest.cpp 
	g++ -std=c++11 createMessages.cpp -o createMessages
	g++ -std=c++11 LogTest.cpp -o LogTest
	g++ -std=c++11 measure.cpp -o measure
	./bench-test-insert.sh
	./bench-test-search.sh
	
clean:
	rm LogTest createMessages measure *~ Log.so Log.o Log
	
test:		test-output test-memory test-time

LogTest:
	g++ -std=c++11 LogTest.cpp -o LogTest 

test-output:	LogTest
	#g++ -std=c++11 LogTest.cpp -o LogTest
	@echo Testing output...
	@(./LogTest < input) > new
	@diff new output
	@rm new

test-memory:	LogTest
	#g++ -std=c++11 LogTest.cpp -o LogTest 
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./LogTest < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
	
test-time:	$(MEASURE) LogTest
	#g++ -std=c++11 LogTest.cpp -o LogTest 
	@echo Testing time...
	@$(MEASURE) ./LogTest < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
	
