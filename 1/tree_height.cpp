// tree_height.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
	int key;
	Node *parent;
	std::vector<Node *> children;

	Node() {
		this->parent = NULL;
	}

	void setParent(Node *theParent) {
		parent = theParent;
		parent->children.push_back(this);
	}
};

int TreeDepth(Node nodes)
{
	vector<int> depth(nodes.children.size());
	if (&nodes == NULL)
		return 0;
	else
	{
		int max = 0;
		for (int i = 0; i < depth.size(); i++)
		{
			depth[i] = TreeDepth(*nodes.children[i]);
			if (depth[i] > max)
				max = depth[i];
		}
		return max + 1;
	}
}

int main_with_large_stack_space() {
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;
	int root;
	std::vector<Node> nodes;
	nodes.resize(n);
	for (int child_index = 0; child_index < n; child_index++) {
		int parent_index;
		std::cin >> parent_index;
		if (parent_index >= 0)
			nodes[child_index].setParent(&nodes[parent_index]);
		else
			root = child_index;
		nodes[child_index].key = child_index;
	}

	// Replace this code with a faster implementation
	/*
	int maxHeight = 0;
	for (int leaf_index = 0; leaf_index < n; leaf_index++) {
		int height = 0;
		for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
			height++;
		maxHeight = std::max(maxHeight, height);
	}
	*/
	//cout << root;
	int maxHeight = TreeDepth(nodes[root]);
	
	std::cout << maxHeight << std::endl;
	system("pause");
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
