#include "QueueElement.h"

QueueElement::QueueElement(cityNameNode* city, int distance) : nextInQueue(nullptr), city(city), distance(distance) {

}
cityNameNode* QueueElement::getCity() {
	return city;
}
QueueElement* QueueElement::getNextInQueue() {
	return nextInQueue;
}
int QueueElement::getDistance() {
	return distance;
}
void QueueElement::setNextInQueue(QueueElement* newNext) {
	nextInQueue = newNext;
}
QueueElement::~QueueElement() {
}