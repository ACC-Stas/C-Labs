#include <iostream>
#include <stack>
#include <queue>

std::queue<int> biggestNumQueue(std::stack<std::queue<int>> st) {
	std::queue<int> currentQ;
	std::queue<int> q;
	int maxNumber = INT32_MIN;
	int currentNumber;
	while (!st.empty()) {
		currentQ = st.top();
		while (!currentQ.empty()) {
			currentNumber = currentQ.front();
			currentQ.pop();
			if (currentNumber > maxNumber) {
				maxNumber = currentNumber;
				q = st.top();
			}
		}
		st.pop();
	}
	return q;
}

std::queue<int> biggestSumQueue(std::stack<std::queue<int>> st) {
	std::queue<int> currentQ;
	std::queue<int> q;
	int maxSum = INT32_MIN;
	int currentSum;
	while (!st.empty()) {
		currentQ = st.top();
		currentSum = 0;
		while (!currentQ.empty()) {
			currentSum += currentQ.front();
			currentQ.pop();
		}
		if (currentSum > maxSum) {
			maxSum = currentSum;
			q = st.top();
		}
		st.pop();
	}
	return q;
}

std::stack<int> mergeStack(std::stack<std::queue<int>> st) {
	std::stack<int> output;
	std::queue<int> q;
	while (!st.empty()) {
		q = st.top();
		while (!q.empty()) {
			output.push(q.front());
			q.pop();
		}
		st.pop();
	}
	return output;
}