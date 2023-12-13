#include "Parser.h"

State Parser::closure(vector<Item> items)
{
    // create current closure (we need 'items' for the return)
    vector<Item> currentClosure = items;

    // closure till you can no more
    bool done = false;
    while (!done)
    {
        // save a copy of the closure for comparison (so you know when to stop)
        vector<Item> oldClosure = currentClosure;
        for (int i = 0; i < currentClosure.size(); ++i)
        {
            auto closureItem = currentClosure[i];
            // if item in closure has dot before non-terminal, expand closure
            if (closureItem.dotPosition < closureItem.rhs.size()
                && this->grammar.nonterminals.find(closureItem.rhs[closureItem.dotPosition])
                != this->grammar.nonterminals.end())
            {
                // go over all the productions of that non-terminal
                string afterDot = closureItem.rhs[closureItem.dotPosition];
                for (auto production : this->grammar.productions[afterDot])
                {
                    // check if item is already in closure
                    Item newItem{ afterDot, production, 0 };
                    bool isItemInCurrentClosure = false;
                    for (Item itemInCurrentClosure : currentClosure)
                        if (itemInCurrentClosure.equals(newItem))
                        {
                            isItemInCurrentClosure = true;
                            break;
                        }
                    
                    // add it if not already in
                    if (!isItemInCurrentClosure) currentClosure.push_back(newItem);
                }
            }
        }
        // stop if closure doesn't modify anymore
        if (currentClosure == oldClosure) done = true;
    }

    return State{items, currentClosure};
}


State Parser::goTo(State state, string atom)
{
    vector<Item> goToItems;

    // go over all items from the states closure
    for (auto item : state.closure)
        // pick the ones that have the atom after the dot
        if (item.dotPosition < item.rhs.size() && item.rhs[item.dotPosition] == atom)
            goToItems.push_back(Item{ item.lhs, item.rhs, item.dotPosition + 1 });

    // check if state already exists, return it if it does
    for (auto otherState : this->cannonicalCollection)
        if (otherState.hasSameClosure(goToItems)) return otherState;

    // find closure if not, and return that new state
    return this->closure(goToItems);
}

void Parser::createCanonicalCollection()
{
    // get closure of first state (which needs to be augmented)
    State firstState = this->closure({ 
        Item{ this->grammar.start, this->grammar.productions[this->grammar.start][0], 0 } 
    });

    // add it to the cannonical collection
    this->cannonicalCollection.push_back(firstState);

    int index = 0;

    // go over all the states
    while (index < this->cannonicalCollection.size())
    {
        // try finding new states using goTo
        auto state = this->cannonicalCollection[index];
        vector<string> atomsAfterDot = state.getAtomAfterDot();
        for (string atom : atomsAfterDot)
        {
            State newState = this->goTo(state, atom);
            if (find(this->cannonicalCollection.begin(), this->cannonicalCollection.end(), newState)
                == this->cannonicalCollection.end())
                this->cannonicalCollection.push_back(newState);
        }
        ++index;
    }
}

string Parser::toString()
{
    string cannonicalString = "";
    for (int i = 0; i < this->cannonicalCollection.size(); ++i)
    {
        cannonicalString += this->cannonicalCollection[i].toString(i) + "\n";
    }

    return cannonicalString;
}
