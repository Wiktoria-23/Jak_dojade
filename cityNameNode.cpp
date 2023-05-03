#include "cityNameNode.h"
cityNameNode::cityNameNode(char* newCityName, int xPosition, int yPosition) : next(nullptr), visited(false), cityName(newCityName), x(xPosition), y(yPosition) {
	adjacentCitiesList = new List<adjacentCityNode>();
}
cityNameNode* cityNameNode::getNextNode() {
	return next;
}
char* cityNameNode::getCityName() const {
	return cityName;
}
int cityNameNode::getX() const {
	return x;
}
int cityNameNode::getY() const {
	return y;
}
List<adjacentCityNode>* cityNameNode::getAdjacentCitiesList() {
	return adjacentCitiesList;
}
void cityNameNode::setVisitedState(bool state) {
	visited = state;
}
bool cityNameNode::getState() const {
	return visited;
}
adjacentCityNode* cityNameNode::findAdjacentCityByName(char* cityName) {
	adjacentCityNode* tmp = adjacentCitiesList->getHead();
	while (tmp != nullptr && !compareText(cityName, tmp->getCityName())) {
		tmp = tmp->getNextNode();
	}
	return tmp;
}
void cityNameNode::addNewAdjacentCity(int distance, char* adjacentCityName) {
	if (findAdjacentCityByName(adjacentCityName) == nullptr) {
		adjacentCityNode* newDestination = new adjacentCityNode(distance, adjacentCityName);
		adjacentCitiesList->addNewLastNode(newDestination);
	}
	else {
		adjacentCityNode* tmp = findAdjacentCityByName(adjacentCityName);
		if (tmp->getDistance() > distance) {
			tmp->setDistance(distance);
		}
	}
}
void cityNameNode::setNextNode(cityNameNode* newNext) {
	next = newNext;
}
cityNameNode::~cityNameNode() {
	if (cityName != nullptr) {
		delete[] cityName;
		cityName = nullptr;
	}
	delete adjacentCitiesList;
	next = nullptr;
}