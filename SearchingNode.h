#pragma once
class SearchingNode
{
private:
	SearchingNode* next;
	int x, y, distance;
public:
	SearchingNode(int newX, int newY, int newDistance);
	void setX(int newX);
	void setY(int newY);
	int getX();
	int getY();
	int getDistance();
	void setNextNode(SearchingNode* newNextNode);
	SearchingNode* getNextNode();
	~SearchingNode();
};

