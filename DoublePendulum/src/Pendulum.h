#ifndef PENDULUM_H
#define PENDULUM_H

#include <vector>
#include "PendulumSection.h"

class Pendulum
{
private:
	std::vector<PendulumSection*> pendulum; //each pendulum can have multiple sections

public:
	Pendulum(int mass, int angle, int length, int x, int y); //constructor
	~Pendulum();

	void start(int mass, int angle, int length, int x, int y); //add first section to pendulum
	void add(int mass, int angle, int length); //add next sections to the pendulum

	void update(); //update pendulum
	void updatePos(int simulationSpeed); //update pendulum position

	void drawArm(sf::RenderWindow& window); //draw pendulums arms
	void drawBody(sf::RenderWindow& window); //draw pendulums bodies
};

#endif / /PENDULUM_H