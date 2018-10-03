// phone_book.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define CONSIZE 10000000

struct Query 
{
	string type, name;
	int number;
};

struct Contact
{
	int number;
	vector<Query> people;
};

vector<Query> read_queries() 
{
	int n;
	cin >> n;
	vector<Query> queries(n);
	for (int i = 0; i < n; ++i) 
	{
		cin >> queries[i].type;
		if (queries[i].type == "add")
			cin >> queries[i].number >> queries[i].name;
		else
			cin >> queries[i].number;
	}
	return queries;
}

void write_responses(const vector<string>& result)
{
	for (size_t i = 0; i < result.size(); ++i)
		cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries)
{
	vector<string> result;
	// Keep list of all existing (i.e. not deleted yet) contacts.
	vector<Contact> contacts;
	contacts.resize(337);
	for (size_t i = 0; i < queries.size(); ++i)
	{
		int T = queries[i].number % 337;
		if (queries[i].type == "add")
		{
			bool was_founded = false;
			// if we already have contact with such number,
			// we should rewrite contact's name

			for (size_t j = 0; j < contacts[T].people.size(); ++j)
				if (contacts[T].people[j].number == queries[i].number)
				{
					contacts[T].people[j].name = queries[i].name;
					was_founded = true;
					break;
				}
			// otherwise, just add it
			if (!was_founded)
				contacts[T].people.push_back(queries[i]);

		}
		else if (queries[i].type == "del")
		{
			for (size_t j = 0; j < contacts[T].people.size(); ++j)
				if (contacts[T].people[j].number == queries[i].number)
				{
					contacts[T].people.erase(contacts[T].people.begin() + j);
					break;
				}
			
		}
		else 
		{
			string response = "not found";
			for (size_t j = 0; j < contacts[T].people.size(); ++j)
				if (contacts[T].people[j].number == queries[i].number)
				{
					response = contacts[T].people[j].name;
					break;
				}
			result.push_back(response);
		}
	}
		return result;
}

int main()
{
	write_responses(process_queries(read_queries()));
	//system("pause");
	return 0;
}
