#include "HashTable.h"
#include "Scanner.h"
#include "FiniteAutomata.h"
#include "Menu.h"
#include "Grammar.h"
#include "Parser.h"
#include "ParserOutput.h"

#include <iostream>

using namespace std;

void testScanner()
{
	FiniteAutomata faIntConst{ "C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week6\\fa_int_const.in" };
	FiniteAutomata faIdentifier{ "C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week6\\fa_identifier.in" };

	Scanner scanner(
		"C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week2\\token.in",
		"C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week2\\separator.in",
		"C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week2\\operator.in",
		"C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week2\\reservedWord.in",
		faIntConst,
		faIdentifier
	);
	try
	{
		scanner.scan("C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week1\\p1.ili");
		vector<string> sequence = scanner.pifToTokenSequence();
		//scanner.displayPif();
		//scanner.dumpToFile();
	}
	catch (runtime_error e)
	{
		cout << e.what();
	}
}

void testFA()
{
	FiniteAutomata faIntConst{ "C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week6\\fa_int_const.in" };
	cout << faIntConst.check("12") << endl;
	cout << faIntConst.check("-12") << endl;
	cout << faIntConst.check("++12") << endl;
	cout << faIntConst.check("0+12") << endl;
	cout << faIntConst.check("-0") << endl;
	cout << faIntConst.check("-a") << endl;
	cout << faIntConst.check("aasdf") << endl;
	cout << faIntConst.check("+aasdf") << endl;
	cout << faIntConst.check("0") << endl;
	cout << faIntConst.check("1231231231") << endl;
	//fa.displayFA();

	FiniteAutomata faIdentifier{ "C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week6\\fa_identifier.in" };
	cout << faIdentifier.check("___") << endl;
	cout << faIdentifier.check("12") << endl;
	cout << faIdentifier.check("_asdf3_") << endl;
	cout << faIdentifier.check("__aAdf3_") << endl;
	cout << faIdentifier.check("_333__") << endl;
	cout << faIdentifier.check("__a_") << endl;
	cout << faIdentifier.check("adf4___") << endl;
	cout << faIdentifier.check("ABFdf4_S__") << endl;
	cout << faIdentifier.check("4___") << endl;
	//faIdentifier.displayFA();

	Menu menu(faIntConst);
	menu.start();
}

void testGrammar() 
{
	try {
		Grammar g{ "C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week8\\g2.txt" };

		g.displayNonTerminals();
		g.displayTerminals();
		g.displayProduction("enriched_symbol");
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

void testParser()
{
	try {
		// lr(0)
		Grammar g{ "C:\\Users\\andre\\Desktop\\folders\\facultate\\sem_5\\compilers\\week8\\g3.txt" };
		Parser p(g);
		p.createCanonicalCollection();

		// parsing table
		p.createParsingTable();
		cout << p.toString();

		int i = 0;
		for (auto row : p.parsingTable)
		{
			cout << "s" << to_string(i++) << ": ";
			switch (row.action)
			{
			case Action::Accept:
				cout << "accept" << endl;
				break;
			case Action::Reduce:
				cout << "reduce " << row.production.toString() << endl;
				break;
			case Action::Shift:
				cout << "shift" << endl;
				for (auto [atom, stateIndex] : row.gotos)
					cout << '\t' << atom << " " << p.cannonicalCollection[stateIndex].toString(stateIndex) << endl;
				break;
			case Action::ShiftReduceConflict:
				cout << "shift-reduce" << endl;
				for (auto [atom, stateIndex] : row.gotos)
					cout << '\t' << atom << " " << p.cannonicalCollection[stateIndex].toString(stateIndex) << endl;
				break;
			default:
				break;
			}
		}
		cout << endl;

		// parsing sequence
		vector<Item> output = p.parse({ "a", "b", "b", "c" });
		for (Item i : output) cout << i.toString() << endl;
		cout << endl;

		// parser output/parsing tree
		ParserOutput po{ g, output };

		po.createParsingTree();
		po.display();
	}
	catch (const string& s)
	{
		cout << s << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

}

void runG1()
{
	try
	{
		Grammar g{ ".\\files\\g1.txt" };
		Parser p(g);

		vector<string> sequence = { "a", "b", "b", "c" };

		p.createCanonicalCollection();
		p.createParsingTable();

		vector<Item> output = p.parse(sequence);

		ParserOutput po{ g, output };

		po.createParsingTree();
		po.display();

		po.saveToFile("out1.txt");
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	catch (const string& e)
	{
		cout << e << endl;
	}
}

void runG2()
{
	try
	{
		FiniteAutomata faIntConst{ ".\\files\\fa_int_const.in" };
		FiniteAutomata faIdentifier{ ".\\files\\fa_identifier.in" };

		Scanner scanner(
			".\\files\\token.in",
			".\\files\\separator.in",
			".\\files\\operator.in",
			".\\files\\reservedWord.in",
			faIntConst,
			faIdentifier
		);

		Grammar g{ ".\\files\\g2.txt" };

		Parser p(g);

		scanner.scan(".\\files\\p1.ili");
		//scanner.displayPif();
		vector<string> sequence = scanner.pifToTokenSequence();

		p.createCanonicalCollection();
		p.createParsingTable();

		vector<Item> output = p.parse(sequence);
		//for (Item i : output) cout << i.toString() << endl;
		//cout << endl;

		ParserOutput po{ g, output };

		po.createParsingTree();
		po.display();

		po.saveToFile("out2.txt");
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	catch (const string& e)
	{
		cout << e << endl;
	}
}

int main() 
{
	//testScanner();
	//testFA();
	//testGrammar();
	//testParser();
	runG1();
	//runG2();

	return 0;
}