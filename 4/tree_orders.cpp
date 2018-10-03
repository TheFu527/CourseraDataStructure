﻿// tree_orders.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
private:
	int n;
	vector <int> key;
	vector <int> left;
	vector <int> right;

	void inOrder(int tree, vector<int> &result)
	{
		if(left[tree]!=-1)
			inOrder(left[tree], result);
		result.push_back(key[tree]);
		if(right[tree]!=-1)
			inOrder(right[tree], result);
		return;
	}

	void preOrder(int tree, vector<int> &result)
	{
		result.push_back(key[tree]);
		if (left[tree] != -1)
			preOrder(left[tree], result);
		if (right[tree] != -1)
			preOrder(right[tree], result);
		return;
	}

	void postOrder(int tree, vector<int> &result)
	{
		if (left[tree] != -1)
			postOrder(left[tree], result);
		if (right[tree] != -1)
			postOrder(right[tree], result);
		result.push_back(key[tree]);
		return;
	}
	

public:
	void read() {
		cin >> n;
		key.resize(n);
		left.resize(n);
		right.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> key[i] >> left[i] >> right[i];
		}
	}


	vector <int> in_order() {
		vector<int> result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		inOrder(0, result);
		return result;
	}

	vector <int> pre_order() {
		vector<int> result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		preOrder(0, result);
		return result;
	}

	vector <int> post_order() {
		vector<int> result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		postOrder(0, result);
		return result;
	}
};

void print(vector <int> a) {
	for (size_t i = 0; i < a.size(); i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << a[i];
	}
	cout << '\n';
}

int main_with_large_stack_space() {
	ios_base::sync_with_stdio(0);
	TreeOrders t;
	t.read();
	print(t.in_order());
	print(t.pre_order());
	print(t.post_order());
	//system("pause");
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}
#endif

	return main_with_large_stack_space();
}

