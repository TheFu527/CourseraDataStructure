// check_brackets_in_code.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket 
{
	Bracket(char type, int position) :
		type(type),
		position(position)
	{}

	bool Matchc(char c)
	{
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() 
{
	string text;
	getline(cin, text);
	bool flag = 0;
	stack <Bracket> opening_brackets_stack;
	
	for (int position = 0; position < text.length(); ++position) 
	{
		char next = text[position];

		if (next == '(' || next == '[' || next == '{')
		{
			opening_brackets_stack.push(Bracket(next, position));
		}
		
		if (next == ')' || next == ']' || next == '}') 
		{
			if (opening_brackets_stack.empty())
			{
				cout << position+1;
				flag = 1;
				break;
			}
			if (opening_brackets_stack.top().Matchc(next))
				opening_brackets_stack.pop();
			else
			{
				cout << position+1;
				flag = 1;
				break;
			}

		}
	}

	// Printing answer, write your code here
	if (opening_brackets_stack.empty() && flag == 0)
		cout << "Success" << endl;
	else if (flag == 0)
		cout << opening_brackets_stack.top().position + 1;
	system("pause");
	return 0;
}
