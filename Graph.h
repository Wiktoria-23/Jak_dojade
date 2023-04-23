#pragma once
#include "cityNameNode.h"
class Graph {
private:
	List<cityNameNode>* cityNames;
	int amount;
public:
	Graph();
	void addNewCityName(char* newCityName, int newCityNameLength);
	void incrementAmount();
	~Graph();
};

