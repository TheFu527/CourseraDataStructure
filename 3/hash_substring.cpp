// hash_substring.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data {
	string pattern, text;
};

unsigned long long hash_func(const string& s, unsigned long long prime, unsigned long long x)
{
	unsigned long long hash = 0;
	for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i]) % prime;
	return hash;
}

vector<unsigned long long> PrecomputeHashes(const string& t, size_t pSize, unsigned long long prime, unsigned long long x)
{
	vector<unsigned long long> H;
	unsigned long long y = 1;
	H.resize(t.size() - pSize + 1);
	string s;
	s = t.substr(t.size() - pSize, pSize);
	
	H[t.size() - pSize] = hash_func(s, prime, x);
	for (size_t i = 1; i <= pSize; i++)
	{
		y = (y*x) % prime;
	}
	for (long long i = t.size() - pSize - 1; i >= 0; i--)
	{
		H[i] = (x*H[i + 1] + t[i] - y*t[i + pSize]) % prime;
	}
	return H;
}

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		cout << output[i] << " ";
	std::cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
	const string& s = input.pattern, t = input.text;
	vector<int> ans;
	unsigned long long x = 1;
	unsigned long long prime = 1000000007;
	/*
	for (size_t i = 0; i + s.size() <= t.size(); ++i)
		if (t.substr(i, s.size()) == s)
			ans.push_back(i);
	*/
	unsigned long long pHash = hash_func(s, prime, x);
	vector<unsigned long long> H = PrecomputeHashes(t, s.size(), prime, x);
	for (size_t i = 0; i <= t.size() - s.size(); i++)
	{
		if (pHash != H[i])
			continue;
		if (t.substr(i, s.size()) == s)
			ans.push_back(i);
	}
	return ans;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	print_occurrences(get_occurrences(read_input()));
	//system("pause");
	return 0;
}
