#pragma once
#include"Flight.h"
#include "Queue.h"

#include"City.h"
// structure to store edges
class FlightGraph {
public:
	City* head; //adjacency list as array of pointers
	// Constructor
	FlightGraph(string fname) {
		head = NULL;
		ifstream fileread;
		string str;
		fileread.open(fname);
		while (getline(fileread, str))
		{
			str += ' ';
			int count = 0;
			int index = 0;
			string ss[7];

			for (int i = 0; i < 7; i++) {
				for (; (str[count] != ' '); count++) {
					ss[index] += str[count];
				}
				index++;
				count++;
			}

			index = 0;
			count=2;

			string stringtemp[8];
			int inttemp[8];

			while(count< 6){
				string output;
				string date = ss[count];
				date += '/';
				int b = 0;

				while (date[b] != '\0')
				{
					if (date[b] == '/' || date[b] == ':')
					{
						stringtemp[index] = output;
						output = "";
						index++;
						b++;
					}
				
					if (date[b] != '\0')
					{
						output += date[b];
						b++;
					}
				}
				count++;
			}
			for (int a = 0; a < 8; a++)
			{
				inttemp[a] = stoi(stringtemp[a]);

			}
			Insert(ss[0], ss[1], inttemp[0], inttemp[1], inttemp[2], inttemp[3], inttemp[4], inttemp[5], inttemp[6], inttemp[7],ss[6]);
		}
	}

	void Insert(string dep,string arr, int day, int month, int year, int dHour, int dSec, int aHour, int aMin,int cost, string airline) {
		if (head == NULL) {
			City* temp = new City(dep,arr,day,month,year,dHour,dSec,aHour,aMin,cost,airline);
			head = temp;
			//cout << temp->getname();
		}
		else {
			City* arrtemp = head;
			City* temp = head;
			while (temp->getname()!= dep && temp->next!=NULL) {
				temp = temp->next;
			}
			while (arrtemp->next != NULL && arrtemp->getname()!=arr) {
				arrtemp = arrtemp->next;
			}
			if (temp->getname() == dep) {
				Flight* ftemp1 = new Flight(arr,day,month,year,dHour,dSec,aHour,aMin,cost,airline);
				temp->addflight(ftemp1, arrtemp);
			}
			else {
				City* tempcity = new City(dep, arr, day, month, year, dHour, dSec, aHour, aMin,cost, airline);
				tempcity->addDest(arr, arrtemp);
				temp->next = tempcity;
				//cout << temp->getname()<<endl;
			}
		}
		return;
	}

	void Display() {
		City* temp = head;
		while (temp != NULL) {
			cout << temp->getname() << endl;
			Flight* ftemp = temp->flights;
			while (ftemp != NULL) {
				ftemp->Display();
				cout << "\n";
				ftemp = ftemp->next;
			}
			temp = temp->next;
		}
		return;
	}

	// Destructor
	~FlightGraph() {
		delete[] head;
	}
	void DisplayFlights(string dep = "", string arr = "", City* ctemp = NULL, FlightQueue* fq = new FlightQueue) {
		int debug = 0;
		City* temp;
		cout << "1";
		if (ctemp == NULL) {
			temp = head;
			fq = new FlightQueue;
			cout << "2";
		}
		else {
			temp = ctemp;
		}
		while (temp->getname() != dep) {
			temp = temp->next;
			cout << debug;
			debug++;
		}
		Flight* ftemp = temp->flights;
		temp->visited = true;
		int x = 0;
		while (ftemp->next != NULL) {
			if (ftemp->getcityname() == arr) {
				cout << debug;
				Flight* ftemp1 = new Flight;
				ftemp1 = ftemp;
				fq->Enqueue(ftemp1);
				fq->display();
				ftemp = ftemp->next;
				fq->Dequeue();
				x++;
			}
			else if (temp->destination[x]->visited==true) {
				ftemp = ftemp->next;
				x++;
			}
			else {
				Flight* ftemp1 = new Flight;
				ftemp1 = ftemp;
				fq->Enqueue(ftemp1);
				DisplayFlights(ftemp->getcityname(), arr, temp->destination[x],fq);
				ftemp = ftemp->next;
				++x;
			}
		}
		temp->visited = false;
		fq->Dequeue();
		return;
	}
};

