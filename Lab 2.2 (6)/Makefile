all: buildMain buildTest runTest

buildMain:
	gcc -std=c89 -o src/main src/main.c src/src.c -lm

buildTest:
	gcc -std=c89 -o src/test src/mainTest.c src/src.c -lm

runTest:
	./src/test
