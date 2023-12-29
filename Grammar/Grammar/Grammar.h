#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> 
#include <cctype>
#include <locale>

using namespace std;

class Grammar
{
public:
	unordered_set<string> terminals;
	unordered_set<string> nonterminals;
	string start;
	unordered_map<string, vector<vector<string>>> productions;
	unordered_map<string, string> specialTerminals{
		{ "EPSILON", "" }, 
		{ "EQUAL", "=" }, 
		{ "IDENTIFIER", "" },
		{ "CONSTANT", "" },
	};

	vector<string> parseTerminalsAndNonTerminals(string input);
	pair<string, vector<vector<string>>> parseProduction(string production);

	Grammar(string file);
	void displayTerminals();
	void displayNonTerminals();
	void displayProductions();
	void displayProduction(string nonterminal);
};