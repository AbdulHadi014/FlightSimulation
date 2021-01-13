#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"Flight.h"

class City {
	string name;
public:
	bool visited;
	City* next;
	Flight* flights;
	City** destination;
	int edgecount;
	
	City(string dep, string arr,int day = 0, int month = 0, int year = 0, int dHour = 0, int dSec = 0, int aHour = 0, int aMin = 0,int cost=0, string ss1 = 0, City* dest = NULL) {
		name = dep;
		visited = false;
		flights = new Flight(arr,day, month, year, dHour, dSec, aHour, aMin,cost, ss1);
		edgecount++;
		destination = new City * [40];
	}

	void addDest(string name, City* dest) {
		int citynum = 0;
		Flight* tempflights = flights;
		while (tempflights->getcityname() != name) {
			if (tempflights == NULL) {
				return;
			}
			citynum++;
			tempflights = tempflights->next;
		}
		destination[citynum] = dest;
		return;
	}

	void addflight(Flight* f1,City* dest=NULL) {
		int x=0;
		Flight* temp = flights;
		if (flights == NULL) {
			flights = f1;
			destination[x] = dest;
			return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
			x++;
		}
		temp->next = f1;
		destination[x] = dest;
	}

	int getedgecount() {
		return edgecount;
	}

	string getname() {
		return name;
	}
};
