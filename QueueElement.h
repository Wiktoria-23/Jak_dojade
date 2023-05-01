#pragma once
#include "cityNameNode.h"
class QueueElement
{
private:
	QueueElement* nextInQueue;
	cityNameNode* city;
	int distance;
public:
	QueueElement(cityNameNode* city, int distance);
	cityNameNode* getCity();
	QueueElement* getNextInQueue();
	int getDistance();
	void setNextInQueue(QueueElement* newNext);
	~QueueElement();
};

