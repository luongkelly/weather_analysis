/*
Kelly Luong
This file contains all the implementations of everything that was declared in the header file
*/

#include <string> 
#include <iostream>
#include <iomanip>

#include "Support.h"

using namespace std;

//This is an operator overload
bool location::operator<(const location &other) const {
	//The function compares two strings and returns true if the first one is smaller
	//This allows it to sort the states alphabetically
	if (state < other.state) {
		return true;
	}
	//It then compares the two cities alphabetically if the states are equal to each other
	else if (city < other.city && state == other.state) {
		return true;
	}
	return false;
}

bool location::operator==(const location &rhs) const {
	if (geocode == rhs.geocode) {
        return true;
    }
    return false;
}

list::node::node(const location &n_station=location()) {
	station = n_station;
	
	total_precip = new float[12];
	max_precip = new float[12];
	min_precip = new float[12];
	total_temp = new int[12];
	max_temp = new int[12];
	min_temp = new int[12];
	N = new int[12];

	for (int i = 0; i < 12; i++) {
		total_precip[i] = 0;
		max_precip[i] = 0;
		min_precip[i] = 0;
		total_temp[i] = 0;
		max_temp[i] = 0;
		min_temp[i] = 0;
		N[i] = 0;
	}

	next = nullptr;
}

//I deleted my arrays to avoid memory leaks
list::node::~node() {
	delete[] total_precip;
	delete[] max_precip;
	delete[] min_precip;
	delete[] total_temp;
	delete[] max_temp;
	delete[] min_temp;
	delete[] N;
}

void list::node::incorp(const data &d) {
//This takes into account zero based indexing
	int i = d.month - 1;
		if (N[i] == 0) {
			max_precip[i] = d.precip;
			min_precip[i] = d.precip;
			max_temp[i] = d.temp;
			min_temp[i] = d.temp;
			total_temp[i] = d.temp;
			total_precip[i] = d.precip;
		}
		else {
			if (d.precip < min_precip[i]) {
				min_precip[i] = d.precip;
			}
			if (d.precip > max_precip[i]) {
				max_precip[i] = d.precip;
			}
			if (d.temp < min_temp[i]) {
				min_temp[i] = d.temp;
			}
			if (d.temp > max_temp[i]) {
				max_temp[i] = d.temp;
			}
			total_precip[i] += d.precip;
			total_temp[i] += d.temp;
		}
	N[i]++;
}

void list::node::print_station() {
	for (int i = 0; i < 42; i++) {
        cout << "-";
    }
    cout << endl;

    cout << station.city << ", " << station.state
        << " (" << station.geocode << ")" << endl;

    for (int j = 0; j < 42; j++) {
        cout << "-";
    }
    cout << endl;
	}

//Prints out all of the data with specific calculations for total and average temp/precip
void list::node::print_data() {
	int i = 0;
	while (i < 12){
        cout << setw(3) << left << month_name(i+1) << ":"
            << setfill(' ') << fixed << setprecision(2) << setw(6) << right << total_precip[i]
            << setfill(' ') << fixed << setprecision(2) << setw(6) << right << total_precip[i] / N[i]
            << setfill(' ') << fixed << setprecision(2) << setw(6) << right << max_precip[i]
            << setfill(' ') << fixed << setprecision(2) << setw(6) << right << min_precip[i] << " :"
            << setfill(' ') << setw(4) << right << total_temp[i] / N[i]
            << setfill(' ') << setw(4) << right << max_temp[i]
            << setfill(' ') << setw(4) << right << min_temp[i] << endl;
		++i;
	}
}

list::list() {
	head = new node();
}

list::~list() {
	while (head->next != nullptr) {
		node *temp = head->next;
		head->next = temp->next;
		delete temp;
	}
	delete head;
}

void list::insert(const location &l, const data &d) {
	//This inserts the first node into a empty linked list
	if (head->next == nullptr) {
		node *newNode = new node(l);
		newNode->incorp(d);
		head->next = newNode;
	}
	else {
		//Entry node is used to gain access to the linked list and to be able to iterate through the linked list
		node *entry = head;
		//Entry keeps iterating if the station is less than location
		while (entry->next != nullptr && entry->next->station < l) {
			entry = entry->next;
		}
		//But it will incorporate the data if it's equal
		if (entry->next != nullptr && entry->next->station == l) {
			entry->next->incorp(d);
		}
		//Otherwise, it'll insert a new node into the linked list
		else {
			node *newNode = new node(l);
			newNode->incorp(d);
			newNode->next = entry->next;
			entry->next = newNode;
		}
	}
}

void list::print(const char *c) {
	node *pointer = head->next;
	//This if statement prints out the data if no specific geocode was given
	if (c == NULL) {
		while (pointer != nullptr) {
			pointer->print_station();
			pointer->print_data();
			//It keeps iterating through the linked list and printing everything out if
			//pointer is not null
			pointer = pointer->next;
		}
	}
	else {
		//This while loop iterates through the linked list until it reaches the specific geocode
		while (c != pointer->station.geocode) {
			pointer = pointer->next;
		}
		//Then prints everything out
		pointer->print_station();
		pointer->print_data();
	}
}

//This function takes an integer and returns the month.
//This function is called on in print data member function to be able to output the months.
string month_name(int i) {
    switch(i) { 
        case 1:
            return "Jan";
            break;
        case 2:
            return "Feb";
            break;
        case 3:
            return "Mar";
            break;
        case 4:
            return "Apr";
            break;
        case 5:
            return "May";
            break;
        case 6:
            return "Jun";
            break;
        case 7:  
            return "Jul";
            break;
        case 8:
            return "Aug";
            break;
        case 9:  
            return "Sep";
            break;
        case 10: 
            return "Oct";
            break;
        case 11: 
            return "Nov";
            break;
        case 12: 
            return "Dec";
            break;

    }   
}     
