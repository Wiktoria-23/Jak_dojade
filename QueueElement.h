#pragma once
#include "cityNameNode.h"
class QueueElement
{
private:
	QueueElement* nextInQueue;
	cityNameNode* city;
public:
	QueueElement(cityNameNode* city);
	cityNameNode* getCity();
	QueueElement* getNextInQueue();
	void setNextInQueue(QueueElement* newNext);
	~QueueElement();
};

