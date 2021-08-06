#ifndef PENDULUM_H
#define PENDULUM_H

#include <vector>
#include "PendulumSection.h"

class Pendulum
{
private:
	std::vector<PendulumSection> pendulum; //each pendulum can have multiple PendulumSections
	std::vector<std::vector<sf::Vertex>> trails; //vector of all trails for this Pendulum. Each pendulum can have 1,2,3,4,etc. bodies. This holds the trails for each body

	sf::Color armColor; //keep track of arm color...helps with style 3

	bool isTrails; //helps us track if we want to create trails or not

	std::string currStyle = "1"; //keeps track of the current style we are on
	std::string trailType = "Fade"; //keeps track of the current trail type we are on. Trail types are "fade", "none", and "always"

public:
	
	Pendulum(int mass, float angle, int length, int x, int y); //constructor

	int getSize(); //return size of pendulum vector
	sf::Color getArmColor(); //returns the arms color

	void start(int mass, float angle, int length, int x, int y); //add first section to pendulum
	void add(int mass, float angle, int length); //add next sections to the pendulum

	void calculatePendulum(); //update pendulum
	void updatePos(float simulationSpeed); //update pendulum position

	void newTrail();//create a new trail
	void updateTrails(std::string trailType); //update trails
	void updateTrailColors(); //update trail colors when "always" is on so if we switch colors or types, the trail colors all change

	void styleOne(); //help change pendulum style to 1
	void styleTwo(); //help change pendulum style to 2
	void styleThree(sf::Color newArmColor); //help change pendulum style to 3

	void drawArm(sf::RenderWindow& window); //draw pendulums arms
	void drawBody(sf::RenderWindow& window); //draw pendulums bodies
	void drawTrail(sf::RenderWindow& window); //draw pendulums trails

	sf::Color getRandomColor(); //get random nice looking and bright color
	sf::Color HSVtoRGB(float H, float S, float V); //converts hsv colors to rgb colors
};

#endif / /PENDULUM_H