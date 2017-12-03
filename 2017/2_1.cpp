#include <iostream>
#include <sstream>
#include <limits>
using namespace std;

int main () {
	string row;

	int sum = 0;

	while (getline (cin, row))
	{
		istringstream stream (row);

		int min = numeric_limits<int>::max ();
		int max = numeric_limits<int>::min ();

		int number;

		while (stream >> number)
		{
			if (number < min) min = number;
			if (number > max) max = number;
		}

		sum += max - min;
	}

	cout << sum << endl;

	return 0;
}
