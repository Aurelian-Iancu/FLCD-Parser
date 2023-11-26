#include "Grammar.h"

#include <fstream>
#include <sstream>
#include <iostream>


#include <algorithm> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(string& s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(string& s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(string& s) {
	rtrim(s);
	ltrim(s);
}

vector<string> Grammar::parseTerminalsAndNonTerminals(string input)
{
	stringstream ss(input);
	vector<string> tokens;
	string token;

	while (getline(ss, token, ' ')) tokens.push_back(token);

	return tokens;
}

pair<string, vector<string>> Grammar::parseProduction(string production)
{
	string nonTerminal = production.substr(0, production.find('='));
	trim(nonTerminal);
	if (this->nonterminals.find(nonTerminal) == this->nonterminals.end())
		throw invalid_argument("Non-terminal does not exist.\n");

	production = production.substr(production.find('=') + 1);
	trim(production);

	vector<string> tokens;
	stringstream ss(production);
	string token;

	while (getline(ss, token, '|'))
	{
		trim(token);
		tokens.push_back(token);
	}

	return { nonTerminal, tokens };
}

bool Grammar::checkCFG() {
	bool ok = true;
	for (const auto& production : this->productions) {
		const string& nonterminal = production.first;
		const vector<string>& productionRules = production.second;

		// Check if the nonterminal exists
		if (this->nonterminals.find(nonterminal) == this->nonterminals.end()) {
			ok = false;
		}
	}

	return ok;
}

Grammar::Grammar(string file)
{
	ifstream f(file);

	string nonterminals, terminals;
	getline(f, nonterminals, '\n');
	getline(f, terminals, '\n');
	getline(f, this->start, '\n');

	vector<string> nonterminalsVector = this->parseTerminalsAndNonTerminals(nonterminals);
	vector<string> terminalsVector = this->parseTerminalsAndNonTerminals(terminals);

	this->nonterminals = unordered_set<string>(nonterminalsVector.begin(), nonterminalsVector.end());
	this->terminals = unordered_set<string>(terminalsVector.begin(), terminalsVector.end());

	string production;
	while (getline(f, production, '\n'))
		this->productions.insert(this->parseProduction(production));
}

void Grammar::displayTerminals()
{
	cout << "Terminals: ";
	for (string terminal : this->terminals)
	{
		cout << terminal << " ";
	}

	cout << '\n';
}

void Grammar::displayNonTerminals()
{
	cout << "Nonterminals: ";
	for (string nonterminal : this->nonterminals)
	{
		cout << nonterminal << " ";
	}

	cout << '\n';
}

void Grammar::displayProductions()
{
	cout << "Productions:\n";
	for (auto it = this->productions.begin(); it != this->productions.end(); ++it)
	{
		cout << it->first << " = ";
		bool first = true;
		for (const string& prod : it->second)
		{
			if (!first) cout << " | ";
			else first = false;
			cout << prod;
		}
		cout << '\n';
	}
}

void  Grammar::displayProduction(string nonterminal)
{
	cout << "Productions:\n";
	auto it = this->productions.find(nonterminal);

	if (it != this->productions.end()) {
		cout << it->first << " = ";
		bool first = true;
		for (const string& prod : it->second) {
			if (!first) cout << " | ";
			else first = false;
			cout << prod;
		}
		cout << '\n';
	}
	else {
		cout << "Nonterminal not found.\n";
	}
}