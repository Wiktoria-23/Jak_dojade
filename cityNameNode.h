#pragma once
#include "List.h"
#include "adjacentCityNode.h"
class cityNameNode {
private:
	List<adjacentCityNode>* adjacentCitiesList;
	cityNameNode* next;
	char* cityName;
	int x;
	int y;
public:
	cityNameNode(char* newCityName, int xPosition, int yPosition);
	char* getCityName();
	int getX();
	int getY();
	void setNextNode(cityNameNode* newNext);
	void addNewAdjacentCity(int distance, char* adjacentCityName);
	cityNameNode* getNextNode();
	~cityNameNode();
};

