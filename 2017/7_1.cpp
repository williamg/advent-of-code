#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct programData_t
{
	string name;
	int weight;
	vector<string> children;

	void print () const
	{
		cout << name << " (" << weight << ")";

		if (children.size () > 0)
		{
			cout << " -> ";

			for (auto const child : children)
			{
				cout << child << " ";
			}
		}

		cout << endl;
	}
};

programData_t parseProgramData (string const &line_)
{
	stringstream str (line_);
	programData_t data;

	str >> data.name;
	str.ignore (line_.size (), '(');

	// EW
	char numBuf[5] = {0};
	str.get (numBuf, 5, ')');
	data.weight = atoi (numBuf);

	str.ignore (line_.size (), '>');

	while (! str.eof ())
	{
		string child;
		str >> child;

		if (child.back () == ',')
			child.pop_back ();

		data.children.push_back (child);
	}

	return data;
}

int main ()
{
	unordered_set<string> children;
	vector<string> programs;

	string line;
	while (getline (cin, line))
	{
		programData_t const data = parseProgramData (line);
		programs.push_back (data.name);
		children.insert (data.children.begin (), data.children.end ());
	}

	for (string program : programs)
	{
		if (children.count (program) == 0)
		{
			cout << program << endl;
			return 0;
		}
	}

	return 1;
}
