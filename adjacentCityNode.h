#pragma once
class adjacentCityNode {
private:
	adjacentCityNode* next;
	int distance;
	char* cityName;
	int cityNameLength;
public:
	adjacentCityNode(int newDistance, char* newCityName, int newCityNameLength);
	void setNextNode(adjacentCityNode* next);
	adjacentCityNode* getNextNode();
	~adjacentCityNode();
};

