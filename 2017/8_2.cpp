#include <algorithm>
#include <assert.h>
#include <iostream>
#include <functional>
#include <sstream>
#include <unordered_map>
using namespace std;

using binaryPred_t = std::function<bool(int, int)>;

std::unordered_map<string, int> registers;

binaryPred_t getop (string const &op_)
{
	if (op_ == ">") return [](int a, int b) { return a > b; };
	if (op_ == "<") return [](int a, int b) { return a < b; };
	if (op_ == ">=") return [](int a, int b) { return a >= b; };
	if (op_ == "<=") return [](int a, int b) { return a <= b; };
	if (op_ == "!=") return [](int a, int b) { return a != b; };

	assert (op_ == "==");
	return [](int a, int b) { return a == b; };
}

int main ()
{
	string line;
	int maxEver = 0;

	while (getline (cin, line))
	{
		stringstream stream (line);

		string regMod;
		stream >> regMod;

		string op;
		stream >> op;

		int val;
		stream >> val;

		string nil;
		stream >> nil;

		string regCond;
		stream >> regCond;

		string condOp;
		stream >> condOp;

		int condVal;
		stream >> condVal;

		int const curVal = registers[regMod];
		int const newVal = (op == "inc" ? curVal + val : curVal - val);

		if (getop (condOp)(registers[regCond], condVal))
		{
			registers[regMod] = newVal;

			if (newVal > maxEver)
				maxEver = newVal;
		}
	}

	cout << maxEver << endl;
	return 0;

}
