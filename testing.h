#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;

class Task
{
public:
	virtual void solve() = 0;
};

void test(Task &t, string testCasesFile = "cases.txt")
{
	ifstream cases(testCasesFile);
	if (!cases.is_open()) throw;

	bool firstLine = true;
	int testCase = 1;
	while (!cases.eof())
	{
		string inputLine;
		stringstream input(""), outputE(""), outputA("");

		if (firstLine)
		{
			getline(cases, inputLine);
			assert(inputLine == "input");
			firstLine = false;
		}

		while (getline(cases, inputLine) && inputLine != "output")
		{
			input.write(inputLine.c_str(), inputLine.size());
			input.write("\n", 1);
		}

		while (getline(cases, inputLine) && inputLine != "input")
		{
			outputE.write(inputLine.c_str(), inputLine.size());
			outputE.write("\n", 1);
			if (cases.eof()) break;
		}

		auto cin_old = cin.rdbuf(input.rdbuf());
		auto cout_old = cout.rdbuf(outputA.rdbuf());

		t.solve();

		cin.rdbuf(cin_old);
		cout.rdbuf(cout_old);

		cout << "Test case " << testCase << ":\t\t";
		outputA.write("\n", 1);
		if (outputA.str() == outputE.str())
			cout << "Accepted\n\n";
		else
		{
			cout << "Failed\n";
			cout << "Expected:\t" << outputE.str() << "\n";
			cout << "Actuall:\t" << outputA.str() << "\n\n";
		}

		++testCase;
	}
}