#pragma once

#include <unordered_set>
#include <string>
#include "Item.h"

using namespace std;

class State
{
private:

public:
	vector<Item> closureItems;
	vector<Item> closure;

	State(vector<Item> closureItems, vector<Item> closure) : closureItems{ closureItems }, closure{ closure } {}

	bool operator==(const State& otherState);

	bool hasSameClosure(const vector<Item>& otherClosure);
	vector<string> getAtomAfterDot();
	string toString(int index);
};