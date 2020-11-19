#include <iostream>
#include "State.h"
using namespace std;

int main() {
	State s(5,5,5);
	cout << "tst" << endl;
	s.print();

	

	// pause to see output.
	cout << "Press any key to continue...";
	cin.get();
	return 1;
}