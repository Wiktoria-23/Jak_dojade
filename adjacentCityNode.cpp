#include "adjacentCityNode.h"
adjacentCityNode::adjacentCityNode(int newDistance, char* newCityName, int newCityNameLength) : distance(newDistance), cityName(newCityName), cityNameLength(newCityNameLength), next(nullptr) {
}
void adjacentCityNode::setNextNode(adjacentCityNode* newNext) {
	next = newNext;
}
adjacentCityNode* adjacentCityNode::getNextNode() {
	return next;
}
adjacentCityNode::~adjacentCityNode() {

}