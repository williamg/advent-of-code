#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

int main (int argc, char **argv)
{
	string phrase;

	unsigned count = 0;

	while (getline (cin, phrase))
	{
		stringstream ss (phrase);
		unordered_set<string> words;

		bool dup = false;

		string word;
		while (ss >> word)
		{
			if (words.find (word) == words.end ())
			{
				words.insert (word);
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
