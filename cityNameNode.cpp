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
void cityNameNode::addNewAdjacentCity(int distance, char* adjacentCityName) {
	adjacentCityNode* newDestination = new adjacentCityNode(distance, adjacentCityName);
	adjacentCitiesList->addNewLastNode(newDestination);
}
void cityNameNode::setNextNode(cityNameNode* newNext) {
	next = newNext;
}
cityNameNode::~cityNameNode() {

}