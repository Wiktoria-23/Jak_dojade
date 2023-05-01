#include "SearchingNode.h"

SearchingNode::SearchingNode(int newX, int newY, int newDistance) : next(nullptr), x(newX), y(newY), distance(newDistance) {

}
void SearchingNode::setX(int newX) {
	x = newX;
}
void SearchingNode::setY(int newY) {
	y = newY;
}
int SearchingNode::getX() {
	return x;
}
int SearchingNode::getY() {
	return y;
}
void SearchingNode::setNextNode(SearchingNode* newNextNode) {
	next = newNextNode;
}
int SearchingNode::getDistance() {
	return distance;
}
SearchingNode* SearchingNode::getNextNode() {
	return next;
}
SearchingNode::~SearchingNode() {

}