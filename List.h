#pragma once
template <typename T> class List {
private:
	T* head;
	T* tail;
public:
	List() {
		head = nullptr;
		tail = nullptr;
	}
	T* getHead() {
		return head;
	}
	T* getTail() {
		return tail;
	}
	void addNewLastNode(T* nextNode) {
		if (head == nullptr) {
			head = nextNode;
			tail = nextNode;
		}
		else {
			tail->setNextNode(nextNode);
			tail = tail->getNextNode();
		}
	}
	void deleteElement(T* element) {
		T* tmp = head;
		T* previous = nullptr;
		while (tmp != element) {
			previous = tmp;
			tmp = tmp->getNextNode();
		}
		if (tmp == head) {
			head = head->getNextNode();
		}
		if (tmp == tail) {
			tail = previous;
		}
		if (previous != nullptr) {
			previous->setNextNode(tmp->getNextNode());
		}
		delete tmp;
	}
	~List() {

	}
};

