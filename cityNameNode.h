#pragma once
#include "List.h"
#include "adjacentCityNode.h"
class cityNameNode {
private:
	List<adjacentCityNode>* adjacentCitiesList;
	cityNameNode* next;
	char* cityName;
	int cityNameLength;
public:
	cityNameNode(int newCityNameLength, char* newCityName);
	void setNextNode(cityNameNode* newNext);
	cityNameNode* getNextNode();
	~cityNameNode();
};

