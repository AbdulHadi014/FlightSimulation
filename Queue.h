#include "Flight.h"




class FlightQueue {
	Flight* front;
	Flight* rear;
public:
	FlightQueue() {
		front = NULL;
		rear = NULL;
	}
	Flight* Dequeue() {
		if (front == NULL) {
			return NULL;
		}
		else {
			Flight* x = front->getflight();
			Flight* temp = front;
			delete temp;
			front = front->next;
			return x;
		}
	}

	void Enqueue(Flight* x) {
		if (front == NULL) {
			front = x;
			rear = x;
			front->next = NULL;
		}
		else {
			rear->next = x;
			rear = x;
			x->next = NULL;
		}
	
		return;
	}


	void clear() {
		Flight* temp = front;
		while (temp != rear) {
			front = front->next;
			delete temp;
			temp = front;
		}
		delete rear;
		front = NULL;
		rear = NULL;
	}
	bool isEmpty() {
		if (front == NULL) {
			return true;
		}
		return false;
	}
	void display() {
		Flight* temp = front;
		while (temp != NULL) {
			temp->Display();
			cout << " ";
			temp = temp->next;
		}
	}
	int queuelength() {
		int x = 0;
		while (front != rear) {
			x++;
			front = front->next;
		}
		return x;
	}
	~FlightQueue() {
		clear();
		delete front;
		delete rear;
	}
};
