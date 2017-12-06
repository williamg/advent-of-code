#include <iostream>
#include <vector>
using namespace std;

int main ()
{
	vector<int> offsets;

	int number;
	while (cin >> number)
		offsets.push_back (number);

	int steps = 0;

	int idx = 0;

	while (idx >= 0 && idx < offsets.size ())
	{
		int newIdx = idx + offsets[idx];

		if (offsets[idx] >= 3)
			offsets[idx]--;
		else
			offsets[idx]++;

		idx = newIdx;
		steps++;
	}

	cout << steps << endl;
	return 0;
}
