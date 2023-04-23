#include "Graph.h"
#include <iostream>
Graph::Graph() : amount(NULL) {
	cityNames = new List<cityNameNode>();
}
void Graph::addNewCityName(char* newCityName, int newCityNameLength) {
	cityNameNode* newCityNameNode = new cityNameNode(newCityNameLength, newCityName);
	cityNames->addNextNode(newCityNameNode);
	incrementAmount();
}
void Graph::incrementAmount() {
	amount += 1;
}
Graph::~Graph() {

}