#pragma once
#include <stack>
#include <queue>

std::queue<int> biggestNumQueue(std::stack<std::queue<int>> st);
std::queue<int> biggestSumQueue(std::stack<std::queue<int>> st);
std::stack<int> mergeStack(std::stack<std::queue<int>> st);