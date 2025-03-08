#include "PriorityQueue.h"
PriorityQueue::PriorityQueue(cityNameNode* startingCity) {
	front = new QueueElement(startingCity, 0);
}
void PriorityQueue::addToQueue(QueueElement* newElement) {
	QueueElement* tmp = front;
	QueueElement* previous = nullptr;
	while (tmp != nullptr && tmp->getDistance() < newElement->getDistance()) {
		previous = tmp;
		tmp = tmp->getNextInQueue();
	}
	if (tmp == nullptr) {
		if (tmp == front) {
			front = newElement;
		}
		else {
			previous->setNextInQueue(newElement);
		}
	}
	if (previous != nullptr) {
		previous->setNextInQueue(newElement);
	}
	else {
		front = newElement;
	}
	newElement->setNextInQueue(tmp);

}
void PriorityQueue::removeFirstFromQueue() {
	QueueElement* tmp = front;
	front = front->getNextInQueue();
	delete tmp;
}
void PriorityQueue::addAllAdjacentCities(Graph* mapGraph, cityNameNode* startingCity, int distanceToCity) {
	adjacentCityNode* nextCity = startingCity->getAdjacentCitiesList()->getHead();
	while (nextCity != nullptr) {
		QueueElement* nextAdjacentCity = new QueueElement(
			mapGraph->findCityByName(nextCity->getCityName()), nextCity->getDistance() + distanceToCity
			);
		addToQueue(nextAdjacentCity);
		nextCity = nextCity->getNextNode();
	}
}
QueueElement* PriorityQueue::getFront() {
	return front;
}
PriorityQueue::~PriorityQueue() {
	if (front != nullptr) {
		QueueElement* tmp = front;
		QueueElement* next = nullptr;
		while (tmp != nullptr) {
			next = tmp->getNextInQueue();
			delete tmp;
			tmp = next;
		}
	}
}