// Homework 1-Questions 2-5 - AERSP 424.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Svetoslav Trayanov 
// 02/20/2024

/******************************************************************************

AERSP 424: Advanced Computer Programming

Homework 1 Spring 2024
Question 2 to 5

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

//Q2 
struct Flight {
	std::string origin;
	std::string destination;
	int distance;
};

//Q3
class Plane {
private:
	double pos;
	double vel;
	double distance;
	bool at_SCE;
	std::string origin;
	std::string destination;
	std::vector<Flight> flights;



public:
	Plane(std::string from, std::string to) // Constructor
	{
		std::vector<Flight> flights = { //part of Q2
			{"SCE", "PHL", 160},
			{"SCE", "ORD", 640},
			{"SCE", "EWR", 220}
		};

		std::string origin = from;
		std::string destination = to;


		//code that does the flight lookup to search for either combination of origin and destination as a valid match. as result we set destination variable to th edestination in our vector from Q2
		bool found = false;
		for (const auto& flight : flights) {
			if ((flight.origin == origin && flight.destination == destination) ||
				(flight.origin == destination && flight.destination == origin)) {
				distance = flight.distance;
				found = true;
				break;
			}

		}

		//Q4
		pos = 0;
		vel = 0;
		at_SCE = 0; 

		std::cout << "Plane created at: " << this << std::endl;
		std::cout << "Flight from " << origin << " to " << destination << std::endl;
	}

	// Destructor thats very simple, you just destroy the previos Plane contstruct and print out
	~Plane() {
		std::cout << "Plane Destroyed" << std::endl;
		std::cout << "############################################ End of Question 2 ##################################\n";
	}

	//function operate
	void operate(double dt)
	{
		if (pos < distance) {
			pos += vel * dt;
			at_SCE = 1;
		}
		else if (destination == "SCE") {
			at_SCE = 1;
			std::string temp = origin;
			origin = destination;
			destination = temp;
			pos = 0;
		}
		else {
			std::string temp = origin;
			origin = destination;
			destination = temp;
			pos = 0;
		}
	}

	
	double getPos() const { return pos; }

	std::string getOrigin() const { return origin; }

	std::string getDestination() const { return destination; }

	bool getAtSCE() const { return at_SCE; }

	// Getter and Setter for velocity
	double getVel() const { return vel; }

	void setVel(double newVel) { vel = newVel; } //that will change the value of the vel member variable from outside the class. (no const here because we want to change the object)

};



int main() {

	//Q5

	std::cout << "############################################### Question 2 #####################################" << std::endl;

	double airplaneSpeed = 500; // hard coded but should they be user entered ??? 
	std::string originAirport = "SCE";
	std::string destinationAirport = "EWR";
	Plane* plane = new Plane(originAirport, destinationAirport);
	plane->setVel(airplaneSpeed);

	double airTime;
	double timeStep = 50;
	int maxIteraions = 1000;

	for (int i = 0; i < maxIteraions; i++) {
		//Simulate a flight	
		if (i == 0) { airTime = 0; }
		else { airTime = timeStep / 3600; } //At momomet 0 you have to use 0 airtime
		plane->operate(airTime); //Function Call to operate
		std::cout << "Time: " << i * timeStep << " seconds, Position: " << plane->getPos() << " miles. \n";
	}


	return 0;
}