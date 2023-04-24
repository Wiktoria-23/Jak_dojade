#pragma once
#include "cityNameNode.h"
class Graph {
private:
	List<cityNameNode>* cityNames;
	int amount;
public:
	Graph();
	void addNewCityName(char* newCityName, int xPosition, int yPosition);
	cityNameNode* findCityByName(char* cityName);
	cityNameNode* findCityByCoordinates(int xPosition, int yPosition);
	void incrementAmount();
	~Graph();
};

