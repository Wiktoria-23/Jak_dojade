#include "adjacentCityNode.h"

adjacentCityNode::adjacentCityNode(int newDistance, char* newCityName)
	: next(nullptr),
	distance(newDistance),
	cityName(newCityName) {
}

void adjacentCityNode::setNextNode(adjacentCityNode* newNext) {
	next = newNext;
}

char* adjacentCityNode::getCityName() const {
	return cityName;
}

int adjacentCityNode::getDistance() const {
	return distance;
}

void adjacentCityNode::setDistance(int newDistance) {
	distance = newDistance;
}

adjacentCityNode* adjacentCityNode::getNextNode() {
	return next;
}

adjacentCityNode::~adjacentCityNode() {
	next = nullptr;
}