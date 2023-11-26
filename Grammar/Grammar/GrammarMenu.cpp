#include <iostream>
#include "Grammar.h"

using namespace std;

void testGrammar()
{
	Grammar g{ "C:\\Users\\Aurelian\\Documents\\GitHub\\Personal\\FLCD-Parser\\Grammar\\Grammar\\Files\\g1.txt" };

	g.displayNonTerminals();
	g.displayTerminals();
	g.displayProduction("A");
}

int main()
{
	//testScanner();
	//testFA();
	testGrammar();

	return 0;
}