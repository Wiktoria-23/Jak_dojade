#pragma once
class SearchingNode
{
private:
	SearchingNode* next;
	int x, y, distance;
public:
	SearchingNode(int newX, int newY, int newDistance);
	int getX() const;
	int getY() const;
	int getDistance() const;
	void setNextNode(SearchingNode* newNextNode);
	SearchingNode* getNextNode();
	~SearchingNode();
};

