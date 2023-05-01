#pragma once
#include "QueueElement.h"
#include "Graph.h"
class PriorityQueue
{
private:
	QueueElement* front;
public:
	PriorityQueue(cityNameNode* startingCity);
	void addToQueue(QueueElement* newElement);
	void removeFirstFromQueue();
	void addAllAdjacentCities(Graph* mapGraph, cityNameNode* startingCity, int distanceToCity);
	QueueElement* getFront();
	~PriorityQueue();
};

