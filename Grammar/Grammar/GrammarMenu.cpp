#include <iostream>
#include "Grammar.h"
#include <string>

using namespace std;

void printMenu() {
	cout << "----------------------------MENU----------------------\n";
	cout << "1. Print nonterminals\n";
	cout << "2. Print terminals\n";
	cout << "3. Print productions\n";
	cout << "4. Print productions for a given nonterminal\n";
	cout << "5. CFG(Context free grammar) check\n";
}

//void testGrammar()
//{
//	Grammar g{ "C:\\Users\\Aurelian\\Documents\\GitHub\\Personal\\FLCD-Parser\\Grammar\\Grammar\\Files\\g1.txt" };
//
//	g.displayNonTerminals();
//	g.displayTerminals();
//	g.displayProduction("A");
//}

void handleInput() {
    int choice;
    string nonterminal;
    Grammar g{ "C:\\Users\\Aurelian\\Documents\\GitHub\\Personal\\FLCD-Parser\\Grammar\\Grammar\\Files\\g1.txt" };

    do {
        printMenu();

        cout << "Enter your choice (1-5, 0 to exit): ";
        cin >> choice;

        switch (choice) {
        case 1:
            g.displayNonTerminals();
            break;
        case 2:
            g.displayTerminals();
            break;
        case 3:
            g.displayProductions();
            break;
        case 4:
            cout << "Enter nonterminal: ";
            cin >> nonterminal;
            g.displayProduction(nonterminal);
            break;
        /*case 5:
            if (g.checkCFG())
            {
                cout << "The grammar is a CFG\n";
            }
            else {
                cout << "The grammar is not a CFG\n";
            }
            break;*/
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 0 and 5.\n";
            break;
        }

    } while (choice != 0);
}

int main()
{
    try {
    handleInput();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Caught invalid_argument exception: " << e.what() << '\n';
    }
	return 0;
}