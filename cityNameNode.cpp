#include "cityNameNode.h"
cityNameNode::cityNameNode(char* newCityName, int xPosition, int yPosition) : cityName(newCityName), next(nullptr), x(xPosition), y(yPosition) {
	adjacentCitiesList = new List<adjacentCityNode>();
}
cityNameNode* cityNameNode::getNextNode() {
	return next;
}
char* cityNameNode::getCityName() {
	return cityName;
}
int cityNameNode::getX() {
	return x;
}
int cityNameNode::getY() {
	return y;
}
List<adjacentCityNode>* cityNameNode::getAdjacentCitiesList() {
	return adjacentCitiesList;
}
void cityNameNode::setVisitedState(bool state) {
	visited = state;
}
bool cityNameNode::getState() {
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

}