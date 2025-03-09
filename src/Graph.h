#pragma once
#include "cityNameNode.h"

class Graph {
private:
	List<cityNameNode>* cityNames;
	int amount;
public:
	Graph();
	void addNewCityName(char* newCityName, int xPosition, int yPosition);
	int getAmount() const;
	cityNameNode* findCityByName(char* cityName);
	cityNameNode* findCityByNumber(int number);
	cityNameNode* findCityByCoordinates(int xPosition, int yPosition);
	void setAllCitiesUnvisited();
	List<cityNameNode>* getCityNames();
	void incrementAmount();
	~Graph();
};

