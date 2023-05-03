#include "SearchingNode.h"

SearchingNode::SearchingNode(int newX, int newY, int newDistance) : next(nullptr), x(newX), y(newY), distance(newDistance) {

}
int SearchingNode::getX() const {
	return x;
}
int SearchingNode::getY() const {
	return y;
}
void SearchingNode::setNextNode(SearchingNode* newNextNode) {
	next = newNextNode;
}
int SearchingNode::getDistance() const {
	return distance;
}
SearchingNode* SearchingNode::getNextNode() {
	return next;
}
SearchingNode::~SearchingNode() {
	next = nullptr;
}