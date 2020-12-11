#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "State.h"
#include "ControllerSettings.h"
#include "Logger.h"
#include "Environment.h"
#include "Util.h"
using namespace std;

int main() {
	// seed rand
	srand(time(NULL));

	// Create logger
	Logger::start(Level::INFO);

	//Shape s(20, 25, 20);
	//ControllerSettings::envShape = s;

	//Shape placedShape(3,4,5);

	//Environment e;
	//vector<State> possibleStates = e.getPossibleStates(placedShape);
	 
	//for(State s : possibleStates)
	//{
	//	Logger::info(s.toString_h());
	//}

	//cout << "# possible locations: " << possibleStates.size() << endl;

	for(int i = 0; i < 100; i++)
	{
		cout << Util::randNormal(0, 2) << endl;
	}


	Logger::close();
	return 1;
}