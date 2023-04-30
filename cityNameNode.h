#pragma once
#include "List.h"
#include "adjacentCityNode.h"
#include "Operation_on_text.h"
class cityNameNode {
private:
	List<adjacentCityNode>* adjacentCitiesList;
	cityNameNode* next;
	bool visited;
	char* cityName;
	int x;
	int y;
public:
	cityNameNode(char* newCityName, int xPosition, int yPosition);
	char* getCityName();
	int getX();
	int getY();
	void setNextNode(cityNameNode* newNext);
	List<adjacentCityNode>* getAdjacentCitiesList();
	adjacentCityNode* findAdjacentCityByName(char* name);
	void setVisitedState(bool state);
	bool getState();
	void addNewAdjacentCity(int distance, char* adjacentCityName);
	cityNameNode* getNextNode();
	~cityNameNode();
};

