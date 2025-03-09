#pragma once

class adjacentCityNode {
private:
	adjacentCityNode* next;
	int distance;
	char* cityName;
public:
	adjacentCityNode(int newDistance, char* newCityName);
	char* getCityName() const;
	int getDistance() const;
	void setDistance(int newDistance);
	void setNextNode(adjacentCityNode* newNext);
	adjacentCityNode* getNextNode();
	~adjacentCityNode();
};

