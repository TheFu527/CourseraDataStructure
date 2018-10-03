// is_bst.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
	int key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void inOrder(int i, vector<int> &result, const vector<Node> &tree)
{
	if (tree[i].left != -1)
		inOrder(tree[i].left, result, tree);
	result.push_back(tree[i].key);
	if (tree[i].right != -1)
		inOrder(tree[i].right, result, tree);
	return;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
	// Implement correct algorithm here
	if (tree.size() == 0)
		return true;
	vector<int> result;
	inOrder(0, result, tree);
	for (int i=0; i < result.size() - 1; i++)
	{
		if (result[i] > result[i + 1])
			return false;
	}
	return true;
}

int main() {
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; ++i) {
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (IsBinarySearchTree(tree)) {
		cout << "CORRECT" << endl;
	}
	else {
		cout << "INCORRECT" << endl;
	}
	//system("pause");
	return 0;
}
