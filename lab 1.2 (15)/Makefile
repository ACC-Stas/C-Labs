all: buildMain buildTest runTest

buildMain:
	gcc -std=c89 -o src/main src/main.c

buildTest:
	gcc -std=c89 -o src/test -Dmain=_main src/main.c src/testMain.c
 
runTest:
	./src/test