#include "QueueElement.h"

QueueElement::QueueElement(cityNameNode* city) : nextInQueue(nullptr), city(city) {

}
cityNameNode* QueueElement::getCity() {
	return city;
}
QueueElement* QueueElement::getNextInQueue() {
	return nextInQueue;
}
void QueueElement::setNextInQueue(QueueElement* newNext) {
	nextInQueue = newNext;
}
QueueElement::~QueueElement() {
}