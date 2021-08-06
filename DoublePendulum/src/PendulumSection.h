#ifndef PENDULUMSECTION_H
#define PENDULUMSECTION_H

#define PI 3.14159265
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class PendulumSection
{
private:

	sf::Vector2f startPosition; //position of start of pendulum 
	int armLength; 
	int mass; 

	float angle; //pendulums angle in radians
	float angularAcceleration; 
	float angularVelocity;

	const float G = 9.81; //gravity

public:
	sf::CircleShape body;
	sf::RectangleShape arm;

	//-------CONTRUCTORS DESTRUCTORS INIT------------
	PendulumSection(int mass, float angle, int armLength, int x, int y); //constructor for the parent pendulum
	PendulumSection(int mass, float angle, int armLength, PendulumSection& upperPendulum); //constructor for the following children pendulums
	void initialize(int mass, float angle, int armLength); //initialize mass angle armlength. initialize the body and arm visuals

	//-------GETTERS AND SETTERS-----------
	sf::Vector2f getEndingPosition(); //returns the end position of the pendulums arm
	int getArmLength(); //retrieve the armLength
	void setArmLength(int newLength); //set the armLength
	void setPosition(sf::Vector2f position); //set position
	void setMass(int mass); //sets mass

	//-----PENDULUM HELPERS------
	void calculatePendulum(PendulumSection& upperPendulum);
	void updatePos(float dt, PendulumSection& upperPendulum, bool isTopSection);

	//------DRAW HELPERS--------
	void drawArm(sf::RenderWindow& window); 
	void drawBody(sf::RenderWindow& window);

};

#endif //PENDULUMSECTION_H