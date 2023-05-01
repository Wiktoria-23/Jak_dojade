#include "Graph.h"
#include <iostream>
Graph::Graph() : amount(NULL) {
	cityNames = new List<cityNameNode>();
}
cityNameNode* Graph::findCityByName(char* cityName) {
	cityNameNode* currentCityName = cityNames->getHead();
	while (true) {
		int i = 0;
		while (currentCityName->getCityName()[i] != END_OF_TEXT) {
			if (currentCityName->getCityName()[i] != cityName[i]) {
				break;
			}
			i++;
		}
		if (currentCityName->getCityName()[i] == END_OF_TEXT && cityName[i] == END_OF_TEXT) {
			return currentCityName;
		}
		currentCityName = currentCityName->getNextNode();
	}
}
int Graph::getAmount() const {
	return amount;
}
cityNameNode* Graph::findCityByNumber(int number) {
	int counter = 0;
	cityNameNode* tmp = cityNames->getHead();
	while (number != counter) {
		tmp = tmp->getNextNode();
		counter += 1;
	}
	return tmp;
}
List<cityNameNode>* Graph::getCityNames() {
	return cityNames;
}
void Graph::setAllCitiesUnvisited() {
	cityNameNode* tmp = getCityNames()->getHead();
	while (tmp != nullptr) {
		tmp->setVisitedState(false);
		tmp = tmp->getNextNode();
	}
}
cityNameNode* Graph::findCityByCoordinates(int xPosition, int yPosition) {
	cityNameNode* currentCityName = cityNames->getHead();
	while (currentCityName != nullptr && (currentCityName->getX() != xPosition || currentCityName->getY() != yPosition)) {
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