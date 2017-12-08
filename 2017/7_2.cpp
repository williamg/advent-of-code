#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct programData_t
{
	string name;
	int weight;
	vector<string> children;
	int childrenWeight;

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

	if (data.children.size () ==  0)
		data.childrenWeight = 0;
	else
		data.childrenWeight = -1;

	return data;
}

int main ()
{
	unordered_set<string> children;
	unordered_map<string, programData_t> programs;

	string line;
	while (getline (cin, line))
	{
		programData_t const data = parseProgramData (line);
		children.insert (data.children.begin (), data.children.end ());
		programs.insert ({data.name, data});
	}

	// Evaluate from the leaves out
	

	// Grab root
	string root;

	for (auto nameDataPair : programs)
	{
		if (children.count (nameDataPair.first) == 0)
			root = nameDataPair.first;
	}

	// Tree is going to contain the tree (except for leaf nodes) such that all
	// nodes with depth d are higher in the stack than those with d-1
	stack<string> tree;

	// We'll use layer to help us construct tree
	queue<string> layer;

	layer.push (root);

	while (! layer.empty ())
	{
		string p = layer.front ();
		layer.pop ();

		programData_t const &d = programs[p];

		for (string const &c : d.children)
			layer.push (c);

		if (d.children.size () > 0)
			tree.push (p);
	}

	while (! tree.empty ())
	{
		programData_t &d = programs[tree.top ()];
		tree.pop ();

		assert (d.childrenWeight == -1);

		multimap<int, programData_t> childrenWeights;

		for (auto const &p : d.children)
		{
			auto child = programs[p];
			childrenWeights.insert ({
				child.weight + child.childrenWeight,
				child
			});
		}

		auto const first = childrenWeights.begin ();
		auto const sameAsFirstRange =
			childrenWeights.equal_range (first->first);

		if (sameAsFirstRange.second == childrenWeights.end ())
		{
			d.childrenWeight = d.children.size () * first->first;
			continue;
		}

		auto const other = sameAsFirstRange.second;
		auto const bad = (childrenWeights.count (other->first) == 1)
			? other : first;
		auto const good = (childrenWeights.count (other->first) == 1)
			? first : other;

		assert (childrenWeights.count (good->first) == d.children.size () - 1);
		assert (childrenWeights.count (bad->first) == 1);

		int desiredWeight = good->first;
		int neededWeight = desiredWeight - bad->second.childrenWeight;
		cout << neededWeight << endl;
		return 0;
	}

	return 1;
}
