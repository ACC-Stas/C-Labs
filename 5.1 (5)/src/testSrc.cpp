#include <iostream>
#include <stack>
#include <queue>
#include <cassert>
#include "src.h"


void testBigNumberQ(std::stack<std::queue<int>> st, int answers[]) {
	std::queue<int> bigNumberQ = biggestNumQueue(st);
	int i = 0;
	while (!bigNumberQ.empty()) {
		assert(answers[i] == bigNumberQ.front());
		i++;
		bigNumberQ.pop();
	}
}

void testSumQ(std::stack<std::queue<int>> st, int answers[]) {
	std::queue<int> bigSumQ = biggestSumQueue(st);
	int i = 0;
	while (!bigSumQ.empty()) {
		assert(answers[i] == bigSumQ.front());
		i++;
		bigSumQ.pop();
	}
}

void testMergeStack(std::stack<std::queue<int>> st, int answers[]) {
	std::stack<int> numbers = mergeStack(st);
	int i = 0;
	while (!numbers.empty()) {
		assert(answers[i] == numbers.top());
		i++;
		numbers.pop();
	}
}

int main() {
	std::queue<int> q1;
	std::queue<int> q2;
	std::queue<int> q3;
	std::queue<int> q4;
	q1.push(10);
	q1.push(20);
	q2.push(5);
	q2.push(100);
	q3.push(15);
	q3.push(99);
	q3.push(10);
	q4.push(11);
	std::stack<std::queue<int>> st;
	st.push(q1);
	st.push(q2);
	st.push(q3);
	st.push(q4);
	std::queue<int> bigNumberQ = biggestNumQueue(st);
	int r1[] = { 5, 100 };
	int r2[] = { 15, 99 , 10 };
	int r3[] = { 20, 10, 100, 5 ,10, 99, 15, 11 };
	testBigNumberQ(st, r1);
	testSumQ(st, r2);
	testMergeStack(st, r3);
	return 0;
}