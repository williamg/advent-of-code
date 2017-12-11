#include <iostream>
#include <vector>
#include <map>
using namespace std;

constexpr size_t NUM_ELEM = 256;

int main ()
{
	vector<size_t> knot;
	for (size_t i = 0; i < NUM_ELEM; ++i)
		knot.push_back (i);

	vector<size_t> lengths;
	size_t l;
	while (cin >> l)
	{
		lengths.push_back (l);
		cin.ignore (1);
	}

	int skip = 0;
	int cur = 0;

	for (size_t l : lengths)
	{
		size_t end = cur + l;

		map<size_t, size_t> indices;

		for (size_t i = 0; i < end - cur; ++i)
		{
			indices[(cur + i) % NUM_ELEM] = knot[(end - i - 1) % NUM_ELEM];
		}

		for (auto pair : indices)
			knot[pair.first] = pair.second;

		cur = (end + skip) % NUM_ELEM;
		skip++;
	}

	cout << knot[0] * knot[1] << endl;
	return 0;
	
}
