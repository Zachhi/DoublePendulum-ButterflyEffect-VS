#include "Pendulum.h"

Pendulum::Pendulum(int mass, int angle, int length, int x, int y)
{
	start(mass, angle, length, x, y);
}
Pendulum::~Pendulum()
{
	for (int i = 0; i < pendulum.size(); i++)
		delete pendulum[i];
}
//start a new pendulum
void Pendulum::start(int mass, int angle, int length, int x, int y)
{
	PendulumSection* currPendulum = new PendulumSection(mass, angle, length, x, y); //create the first arm+body for this new pendulum object
	pendulum.push_back(currPendulum);
}
//add to the existing pendulum
void Pendulum::add(int mass, int angle, int length)
{
	PendulumSection* currPendulum = new PendulumSection(mass, angle, length, pendulum[pendulum.size()-1]);//mass, angle, arm length, upper pendulum
	pendulum.push_back(currPendulum);
}

//update pendulum's values
void Pendulum::update()
{
	for (int i = pendulum.size(); i > 1; i--) //start from bottom pendulum up, dont do top pendulum
	{
		pendulum[i-1]->updatePendulum();
	}
}
//update pendulums position
void Pendulum::updatePos(int simulationSpeed)
{
	for (int i = 0; i < pendulum.size(); i++)
	{
		pendulum[i]->updatePos(simulationSpeed);
	}
}

//draw the arms
void Pendulum::drawArm(sf::RenderWindow& window)
{
	for (int i = 0; i < pendulum.size(); i++)
		pendulum[i]->drawArm(window);
}
//draw the bodies
void Pendulum::drawBody(sf::RenderWindow& window)
{
	for (int i = 0; i < pendulum.size(); i++)
		pendulum[i]->drawBody(window);
}
