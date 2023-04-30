#include "adjacentCityNode.h"
adjacentCityNode::adjacentCityNode(int newDistance, char* newCityName) : distance(newDistance), cityName(newCityName), next(nullptr) {
}
void adjacentCityNode::setNextNode(adjacentCityNode* newNext) {
	next = newNext;
}
char* adjacentCityNode::getCityName() {
	return cityName;
}
int adjacentCityNode::getDistance() {
	return distance;
}
void adjacentCityNode::setDistance(int newDistance) {
	distance = newDistance;
}
adjacentCityNode* adjacentCityNode::getNextNode() {
	return next;
}
adjacentCityNode::~adjacentCityNode() {

}