// rope.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

class Rope {
	string s;
	struct Vertex {
		int key;
		// Sum of all the keys in the subtree - remember to update
		// it after each operation that changes the tree.
		//long long sum;
		char word;
		Vertex* left;
		Vertex* right;
		Vertex* parent;

		Vertex(int key, char word, Vertex* left, Vertex* right, Vertex* parent)
			: key(key), word(word), left(left), right(right), parent(parent) {}
	};

	void update(Vertex* v) {
		if (v == NULL) return;
		v->key = v->key + (v->left != NULL ? v->left->key : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
		if (v->left != NULL) {
			v->left->parent = v;
		}
		if (v->right != NULL) {
			v->right->parent = v;
		}
	}
	
	void small_rotation(Vertex* v) {
		Vertex* parent = v->parent;
		if (parent == NULL) {
			return;
		}
		Vertex* grandparent = v->parent->parent;
		if (parent->left == v) {
			Vertex* m = v->right;
			v->right = parent;
			parent->left = m;
		}
		else {
			Vertex* m = v->left;
			v->left = parent;
			parent->right = m;
		}
		//update(parent);
		//update(v);
		v->parent = grandparent;
		if (grandparent != NULL) {
			if (grandparent->left == parent) {
				grandparent->left = v;
			}
			else {
				grandparent->right = v;
			}
		}
	}

	void big_rotation(Vertex* v) {
		if (v->parent->left == v && v->parent->parent->left == v->parent) {
			// Zig-zig
			small_rotation(v->parent);
			small_rotation(v);
		}
		else if (v->parent->right == v && v->parent->parent->right == v->parent) {
			// Zig-zig
			small_rotation(v->parent);
			small_rotation(v);
		}
		else {
			// Zig-zag
			small_rotation(v);
			small_rotation(v);
		}
	}

	// Makes splay of the given vertex and makes
	// it the new root.
	void splay(Vertex*& root, Vertex* v) {
		if (v == NULL) return;
		while (v->parent != NULL) {
			if (v->parent->parent == NULL) {
				small_rotation(v);
				break;
			}
			big_rotation(v);
		}
		root = v;
	}

	// Searches for the given key in the tree with the given root
	// and calls splay for the deepest visited node after that.
	// If found, returns a pointer to the node with the given key.
	// Otherwise, returns a pointer to the node with the smallest
	// bigger key (next value in the order).
	// If the key is bigger than all keys in the tree, 
	// returns NULL.
	Vertex* find(Vertex*& root, int key) {
		Vertex* v = root;
		Vertex* last = root;
		Vertex* next = NULL;
		while (v != NULL) {
			if (v->key >= key && (next == NULL || v->key < next->key)) {
				next = v;
			}
			last = v;
			if (v->key == key) {
				break;
			}
			if (v->key < key) {
				v = v->right;
			}
			else {
				v = v->left;
			}
		}
		splay(root, last);
		return next;
	}

	void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
		right = find(root, key);
		splay(root, right);
		if (right == NULL) {
			left = root;
			return;
		}
		left = right->left;
		right->left = NULL;
		if (left != NULL) {
			left->parent = NULL;
		}
		update(left);
		update(right);
	}

	Vertex* merge(Vertex* left, Vertex* right) {
		if (left == NULL) return right;
		if (right == NULL) return left;
		Vertex* min_right = right;
		while (min_right->left != NULL) {
			min_right = min_right->left;
		}
		splay(right, min_right);
		right->left = left;
		update(right);
		return right;
	}

	Vertex* root = NULL;

	void insert(int x,char word) {
		Vertex* left = NULL;
		Vertex* right = NULL;
		Vertex* new_vertex = NULL;
		split(root, x, left, right);
		if (right == NULL || right->key != x) {
			new_vertex = new Vertex(x, word, NULL, NULL, NULL);
		}
		root = merge(merge(left, new_vertex), right);
	}


public:
	Rope(const string &s) : s(s) {
	}

	void input()
	{
		for (int i = 0; i < s.size(); i++)
		{
			insert(i, s[i]);
		}
	}

	void process(int i, int j, int k) {
		// Replace this code with a faster implementation
		//string t = s.substr(0, i) + s.substr(j + 1);
		//s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
		Vertex* left = NULL;
		Vertex* middle = NULL;
		Vertex* right = NULL;
		split(root, i, left, middle);
		split(middle, j + 1, middle, right);
		//cout << middle->word << endl;
		//cout << left->key << ' ' << right->key << ' ' << middle->key << endl;
		root = merge(left, right);
		find(root, k);

	}

	string result() {
		return s;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	Rope rope(s);
	int actions;
	cin >> actions;
	rope.input();
	for (int action_index = 0; action_index < actions; ++action_index) {
		int i, j, k;
		cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	cout << rope.result() << endl;
	system("pause");
	return 0;
}

