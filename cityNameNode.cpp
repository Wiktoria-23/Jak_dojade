#include "cityNameNode.h"
cityNameNode::cityNameNode(int newCityNameLength, char* newCityName) : cityNameLength(newCityNameLength), cityName(newCityName), next(nullptr) {
	adjacentCitiesList = new List<adjacentCityNode>();
}
cityNameNode* cityNameNode::getNextNode() {
	return next;
}
void cityNameNode::setNextNode(cityNameNode* newNext) {
	next = newNext;
}
cityNameNode::~cityNameNode() {

}