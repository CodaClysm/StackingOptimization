#include "ControllerSettings.h"

Shape ControllerSettings::envShape = Shape(0,0,0);
vector<int> ControllerSettings::shapesToPack = vector<int>();
vector<AbsFeature*> ControllerSettings::features = vector<AbsFeature*>();
vector<Shape> ControllerSettings::possibleShapes = vector<Shape>();