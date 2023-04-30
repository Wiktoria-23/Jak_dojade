#pragma once
class adjacentCityNode {
private:
	adjacentCityNode* next;
	int distance;
	char* cityName;
public:
	adjacentCityNode(int newDistance, char* newCityName);
	char* getCityName();
	int getDistance();
	void setNextNode(adjacentCityNode* next);
	adjacentCityNode* getNextNode();
	~adjacentCityNode();
};

