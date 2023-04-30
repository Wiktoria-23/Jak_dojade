#pragma once
#include "QueueElement.h"
#include "Graph.h"
class PriorityQueue
{
private:
	QueueElement* front;
	QueueElement* rear;
public:
	PriorityQueue(cityNameNode* startingCity, Graph* mapGraph);
	void addToQueue(QueueElement* newElement);
	void addToQueueFront(QueueElement* newElement);
	void removeFirstFromQueue();
	void addAllAdjacentCities(Graph* mapGraph, cityNameNode* startingCity);
	QueueElement* getFront();
	~PriorityQueue();
};

