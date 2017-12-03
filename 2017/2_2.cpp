#include <assert.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
using namespace std;

int main () {
	string row;

	int sum = 0;

	while (getline (cin, row))
	{
		istringstream stream (row);

		int number;
		vector<int> numbers;

		while (stream >> number)
			numbers.push_back (number);

		bool found = false;

		for (size_t i = 0; i < numbers.size (); ++i)
		{
			for (size_t j = i + 1; j < numbers.size (); ++j)
			{
				int const big = max (numbers[i], numbers[j]);
				int const small = min (numbers[i], numbers[j]);

				if (big % small == 0)
				{
					sum += big / small;
					found = true;
					break;
				}
			}

			if (found)
				break;
		}

		assert (found);
	}

	cout << sum << endl;

	return 0;
}
