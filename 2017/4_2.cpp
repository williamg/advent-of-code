#include <array>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

array<int, 26> hist (string word)
{
	std::array<int, 26> hist;
	hist.fill (0);

	for (char c : word)
		hist[static_cast<unsigned> (c - 'a')]++;

	return hist;
}

int main (int argc, char **argv)
{
	string phrase;

	unsigned count = 0;

	while (getline (cin, phrase))
	{
		stringstream ss (phrase);
		set<array<int, 26>> words;

		bool dup = false;

		string word;
		while (ss >> word)
		{
			auto histo = hist (word);
			if (words.find (histo) == words.end ())
			{
				words.insert (histo);
			}
			else
			{
				dup = true;
				break;
			}
		}

		if (! dup)
			count++;
	}

	cout << count << endl;
	return 0;
}
