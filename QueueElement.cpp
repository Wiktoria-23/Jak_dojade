#include "QueueElement.h"

QueueElement::QueueElement(cityNameNode* city, int distance) : nextInQueue(nullptr), city(city), distance(distance) {

}
cityNameNode* QueueElement::getCity() const {
	return city;
}
QueueElement* QueueElement::getNextInQueue() const {
	return nextInQueue;
}
int QueueElement::getDistance() const {
	return distance;
}
void QueueElement::setNextInQueue(QueueElement* newNext) {
	nextInQueue = newNext;
}
QueueElement::~QueueElement() {
}