#include "PriorityQueue.h"
PriorityQueue::PriorityQueue(cityNameNode* startingCity) {
	front = new QueueElement(startingCity);
	rear = nullptr;
}
void PriorityQueue::addToQueueFront(QueueElement* newElement) {
	QueueElement* previousFront = front;
	front = newElement;
	newElement->setNextInQueue(previousFront);
}
void PriorityQueue::removeFirstFromQueue() {
	QueueElement* tmp = front;
	front = front->getNextInQueue();
	delete tmp;
}
void PriorityQueue::addAllAdjacentCities(Graph* mapGraph, cityNameNode* startingCity) {
	adjacentCityNode* nextCity = startingCity->getAdjacentCitiesList()->getHead();
	while (nextCity != nullptr) {
		QueueElement* nextAdjacentCity = new QueueElement(mapGraph->findCityByName(nextCity->getCityName()));
		if (mapGraph->findCityByName(nextAdjacentCity->getCity()->getCityName())->getState() == false) {
			addToQueueFront(nextAdjacentCity);
		}
		nextCity = nextCity->getNextNode();
	}
}
QueueElement* PriorityQueue::getFront() {
	return front;
}
PriorityQueue::~PriorityQueue() {

}