all: buildMain buildTest runTest

buildMain:
	g++ -o src/main src/Employee.cpp src/Project.cpp src/Task.cpp src/main.cpp

buildTest:
	g++ -ftest-coverage -fprofile-arcs -O0 -o src/test src/test.cpp src/Task.cpp src/Project.cpp src/Employee.cpp

runTest:
	./src/test
	gcov -abcfu Employee.cpp
	gcov -abcfu Task.cpp
	gcov -abcfu Project.cpp
	