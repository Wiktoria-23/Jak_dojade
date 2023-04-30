#include "QueueElement.h"

QueueElement::QueueElement(cityNameNode* city) : city(city), nextInQueue(nullptr) {

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