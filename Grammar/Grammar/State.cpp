#include "State.h"

bool State::operator==(const State& otherState)
{
	if (this->closure.size() != otherState.closure.size()) return false;
	for (auto item : this->closure)
	{
		bool found = false;
		for (Item otherItem : otherState.closure)
		{
			if (item.equals(otherItem)) found = true;
		}
		if (!found) return false;
	}

	return true;
}

bool State::hasSameClosure(const vector<Item>& otherClosure)
{
	if (this->closureItems.size() != otherClosure.size()) return false;

	for (auto item : this->closureItems)
	{
		bool foundItem = false;
		for (Item otherItem : otherClosure)
			if (item.equals(otherItem)) 
			{ 
				foundItem = true; 
				break; 
			}
		if (!foundItem) return false;
	}

	return true;
}
 
vector<string> State::getAtomAfterDot()
{
	vector<string> atoms;
	for (auto item : this->closure)
		if (item.dotPosition < item.rhs.size())
			atoms.push_back(item.rhs[item.dotPosition]);

	return atoms;
}

string State::toString(int index)
{
	string stateString = "s" + to_string(index) + " = closure({ ";
	for (int i = 0; i < this->closureItems.size(); ++i)
	{
		auto item = this->closureItems[i];
		stateString += item.toString();
		if (i != this->closureItems.size() - 1)
			stateString += ", ";
	}
	stateString += " }) = { ";
	for (int i = 0; i < this->closure.size(); ++i)
	{
		auto item = this->closure[i];
		stateString += item.toString();
		if (i != this->closure.size() - 1)
			stateString += ", ";
	}
	stateString += " }";

	return stateString;
}
