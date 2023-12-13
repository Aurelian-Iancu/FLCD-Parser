#include "Connection.h"

Connection::Connection(State startingState, State finalState, std::string symbol):
startingState(startingState),finalState(finalState),symbol(symbol){}

