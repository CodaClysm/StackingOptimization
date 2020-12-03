#include <iostream>
#include "State.h"
#include "ControllerSettings.h"
#include "Logger.h"
#include "Environment.h"
#include <vector>
using namespace std;

int main() {
	// Create logger
	Logger::start(Level::INFO);

	Shape s(20, 25, 20);
	ControllerSettings::envShape = s;

	Shape placedShape(3,4,5);

	Environment e;
	vector<State> possibleStates = e.getPossibleStates(placedShape);
	 
	for(State s : possibleStates)
	{
		Logger::info(s.toString_h());
	}

	cout << "# possible locations: " << possibleStates.size() << endl;
	Logger::close();
	// pause to see output.
	cout << "Press any key to continue...";
	cin.get();
	return 1;
}