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

	PendulumSection* upperPendulum = nullptr; //tracks its parent pendulum
	PendulumSection* lowerPendulum = nullptr; //tracks its child pendulum
	
	sf::CircleShape* body; 
	sf::RectangleShape* arm;

public:
	//-------CONTRUCTORS DESTRUCTORS INIT------------
	PendulumSection(int mass, float angle, int armLength, int x, int y); //constructor for the parent pendulum
	PendulumSection(int mass, float angle, int armLength, PendulumSection* upperPendulum); //constructor for the following children pendulums
	void initialize(int mass, float angle, int armLength); //initialize mass angle armlength. initialize the body and arm visuals
	~PendulumSection(); //destructor

	//-------GETTERS-----------
	sf::Vector2f getEndingPosition(); //returns the end position of the pendulums arm

	//-----PENDULUM HELPERS------
	void updatePendulum();
	void updatePos(float dt);
	void joinPendulums(PendulumSection* lowerPendulum);

	//------DRAW HELPERS--------
	void drawArm(sf::RenderWindow& window); 
	void drawBody(sf::RenderWindow& window);
};

#endif //PENDULUMSECTION_H