#include "Graph.h"
#include <iostream>
Graph::Graph() : amount(NULL) {
	cityNames = new List<cityNameNode>();
}
cityNameNode* Graph::findCityByName(char* cityName) {
	cityNameNode* currentCityName = cityNames->getHead();
	while (currentCityName->getCityName() != cityName) {
		currentCityName = currentCityName->getNextNode();
	}
	return currentCityName;
}
cityNameNode* Graph::findCityByCoordinates(int xPosition, int yPosition) {
	cityNameNode* currentCityName = cityNames->getHead();
	while (currentCityName!= nullptr && currentCityName->getX() != xPosition && currentCityName->getY() != yPosition) {
		currentCityName = currentCityName->getNextNode();
	}
	return currentCityName;
}
void Graph::addNewCityName(char* newCityName, int xPosition, int yPosition) {
	cityNameNode* newCityNameNode = new cityNameNode(newCityName, xPosition, yPosition);
	cityNames->addNewLastNode(newCityNameNode);
	incrementAmount();
}
void Graph::incrementAmount() {
	amount += 1;
}
Graph::~Graph() {

}