// hash_chains.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
	string type, s;
	size_t ind;
};

struct Element {
	vector<Query> elems;
};

class QueryProcessor {
	int bucket_count;
	// store all strings in one vector
	vector<Element> elements;
	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {
		elements.resize(bucket_count);
	}
	
	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		
		if (query.type == "check") {
			// use reverse order, because we append strings to the end
			for (int i = static_cast<int>(elements[query.ind].elems.size()) - 1; i >= 0; --i)
				cout << elements[query.ind].elems[i].s << " ";
			cout << "\n";
		}
		else {
			
			size_t T = hash_func(query.s);
			if (query.type == "find")
			{
				bool flag = 0;
				for (int i = 0; i < elements[T].elems.size(); i++)
				{
					if (elements[T].elems[i].s == query.s)
					{
						flag = 1;
						break;
					}
				}
				writeSearchResult(flag);
			}
			else if (query.type == "add")
			{
				bool flag = 0;
				for (int i = 0; i < elements[T].elems.size(); i++)
				{
					if (elements[T].elems[i].s == query.s)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					elements[T].elems.push_back(query);
			}
			else if (query.type == "del")
			{
				for (int i = 0; i < elements[T].elems.size(); i++)
				{
					if (elements[T].elems[i].s == query.s)
					{
						elements[T].elems.erase(elements[T].elems.begin()+i);
						break;
					}
				}
			}
			/*
			vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
			if (query.type == "find")
				writeSearchResult(it != elems.end());
			else if (query.type == "add") {
				if (it == elems.end())
					elems.push_back(query.s);
			}
			else if (query.type == "del") {
				if (it != elems.end())
					elems.erase(it);
			}
			*/
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	system("pause");
	return 0;
}
