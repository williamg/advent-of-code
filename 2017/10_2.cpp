#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

constexpr size_t NUM_ELEM = 256;
constexpr size_t NUM_ROUNDS = 64;
vector<size_t> SUFFIX ({17, 31, 73, 47, 23});

int main ()
{
	vector<size_t> knot;
	for (size_t i = 0; i < NUM_ELEM; ++i)
		knot.push_back (i);

	vector<size_t> lengths;
	char c;
	while (cin >> c)
		lengths.push_back (static_cast<size_t> (c));

	for (size_t l : SUFFIX)
		lengths.push_back (l);

	int skip = 0;
	int cur = 0;

	for (size_t r = 0; r < NUM_ROUNDS; ++r)
	{
		for (size_t l : lengths)
		{
			size_t end = cur + l;

			map<size_t, size_t> indices;

			for (size_t i = 0; i < end - cur; ++i)
				indices[(cur + i) % NUM_ELEM] = knot[(end - i - 1) % NUM_ELEM];

			for (auto pair : indices)
				knot[pair.first] = pair.second;

			cur = (end + skip) % NUM_ELEM;
			skip++;
		}
	}

	vector<size_t> dense;
	size_t hash = 0;

	for (size_t i = 0; i < NUM_ELEM; ++i)
	{
		hash ^= knot[i];

		if (i % 16 == 15)
		{
			dense.push_back (hash);
			hash = 0;
		}
	}

	for (size_t v : dense)
		cout << setw(2) << setfill('0') << std::hex << v;

	cout << endl;
	return 0;
	
}
