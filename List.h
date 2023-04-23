#pragma once
template <typename T>
class List {
private:
	T* head;
	T* tail;
public:
	List() : head(nullptr), tail(nullptr) {
	}
	void addNextNode(T* nextNode) {
		if (head == nullptr) {
			head = nextNode;
			tail = nextNode;
		}
		else {
			tail->setNextNode(nextNode);
			tail = tail->getNextNode();
		}
	}
	~List() {

	}
};

