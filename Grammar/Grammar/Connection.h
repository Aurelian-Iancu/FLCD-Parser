#pragma once
#include "State.h"

class Connection {	
private:
	State startingState;
	State finalState;
	std::string symbol;
public:
	Connection(State startingState, State finalState, std::string symbol);
	State getStartingState() { return this->startingState; };
	State getFinalState() { return this->finalState; };
	std::string getSymbol() { return this->symbol; };
};
