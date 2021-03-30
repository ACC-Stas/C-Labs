all: buildMain buildTest runTest

buildMain:
	gcc -std=c89 -o src/main src/main.c src/src.c

buildTest:
	gcc -std=c89 -o src/test src/srcTest.c src/src.c

runTest:
	./src/test dictionary.txt src/dictionary.txt src/text.txt