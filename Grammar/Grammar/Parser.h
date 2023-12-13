#pragma once

#include "State.h"
#include "Item.h"
#include "Grammar.h"
#include <vector>
#include <algorithm>
#include "Connection.h"

using namespace std;

class Parser
{
private:
	Grammar grammar;
	vector<State> cannonicalCollection;
	vector<Connection> connections;
public:
	Parser(Grammar grammar) : grammar{ grammar } {}

	State closure(vector<Item> items);
	State goTo(State state, string atom);
	void createCanonicalCollection();

	vector<Connection> getConnectionsOfState(State state);

	string toString();
};