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
	cityNameNode* getCity() const;
	QueueElement* getNextInQueue() const;
	int getDistance() const;
	void setNextInQueue(QueueElement* newNext);
	~QueueElement();
};

