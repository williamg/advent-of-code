#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

constexpr size_t const NUM_BANKS = 16;
using banks_t = std::array<int, NUM_BANKS>;

namespace std
{
template<> struct hash<banks_t>
{
size_t operator ()(banks_t const &val_) const
{
	size_t v = 0;
	for (size_t i = 0; i < NUM_BANKS; ++i)
		v *= val_[i];

	return v;
}
};
}

int main ()
{
	banks_t config;
	unordered_set<banks_t> alreadySeen;

	for (size_t i = 0; i < NUM_BANKS; ++i)
		cin >> config[i];

	int iters = 0;

	while (alreadySeen.count (config) == 0)
	{
		alreadySeen.insert (config);

		int maxIdx = NUM_BANKS - 1;

		for (size_t i = 0; i < NUM_BANKS - 1; ++i)
		{
			if (config[NUM_BANKS - i - 2] >= config[maxIdx])
				maxIdx = NUM_BANKS - i - 2;
		}

		int toDistribute = config[maxIdx];

		config[maxIdx] = 0;

		int idx = (maxIdx + 1) % NUM_BANKS;

		while (toDistribute > 0)
		{
			config[idx]++;
			toDistribute--;

			idx = (idx + 1) % NUM_BANKS;
		}

		++iters;
	}

	cout << iters << endl;
	return  0;
}
