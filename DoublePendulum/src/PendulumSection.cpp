#include "PendulumSection.h"
#define LOG(x) std::cout << x << std::endl

//-----------CONTRUCTORS DESTRUCTOR INIT---------
//constructor for the parent pendulum
PendulumSection::PendulumSection(int mass, float angle, int armLength, int x, int y) 
{
	this->startPosition.x = x;
	this->startPosition.y = y;
	initialize(mass, angle, armLength); //help initialize mass, angle, and armLength
}
//constructor for the following children pendulums
PendulumSection::PendulumSection(int mass, float angle, int armLength, PendulumSection& upperPendulum)
{
	startPosition = upperPendulum.getEndingPosition();
	initialize(mass, angle, armLength);
}
//initialize mass angle armLength. initialize the body and arm visuals
void PendulumSection::initialize(int mass, float angle, int armLength)
{
	this->mass = mass;
	this->armLength = armLength;
	this->angle = angle * PI / 180; //convert to radians

	angularAcceleration = 0;
	angularVelocity = 0;

	//create the arm visual
	arm.setSize(sf::Vector2f(10, this->armLength)); //set width, length of arm
	arm.setOrigin(this->arm.getSize().x / 2, 0); //set orgin in middle at top of rectangle
	arm.setPosition(sf::Vector2f(this->startPosition.x, this->startPosition.y));
	arm.setFillColor(sf::Color(156, 156, 156));
	arm.setRotation(angle);
	arm.setOutlineColor(sf::Color::Black);
	arm.setOutlineThickness(2);

	//create the body visual
	body.setRadius((mass/5.0f));
	body.setOrigin(sf::Vector2f(this->body.getRadius(), this->body.getRadius())); //set orgin as center of circle
	body.setPosition(getEndingPosition());
	body.setOutlineColor(sf::Color::Black);
	body.setOutlineThickness(3);
	body.setFillColor(sf::Color(219, 219, 219));
}

//-----------GETTERS------------
sf::Vector2f PendulumSection::getEndingPosition() //returns the end position of the pendulums arm
{
	sf::Vector2f endingPosition;
	endingPosition.x = this->startPosition.x - this->armLength * sin(angle);
	endingPosition.y = this->startPosition.y + this->armLength * cos(angle);
	return(endingPosition);
}
int PendulumSection::getArmLength()
{
	return armLength;
}
void PendulumSection::setArmLength(int newLength)
{
	armLength = newLength;
}
void PendulumSection::setPosition(sf::Vector2f position)
{
	startPosition = position;
}
void PendulumSection::setMass(int mass)
{
	this->mass = mass;
}

//-----------PENDULUM HELPERS-------
void PendulumSection::updatePos(float dt, PendulumSection& upperPendulum, bool isTopSection)
{
	if (!isTopSection) //if it isnt the first section of the pendulum, do this
	{
		startPosition = upperPendulum.getEndingPosition();
	}

	//update angular velocity and the angle
	angularVelocity += angularAcceleration * dt;
	angle += angularVelocity * dt;

	//update visuals
	arm.setPosition(startPosition.x, startPosition.y);
	arm.setRotation(angle * (180 / PI));
	body.setPosition(this->getEndingPosition());
}
void PendulumSection::calculatePendulum(PendulumSection& upperPendulum)
{
		//set the variables we need
		float m1 = upperPendulum.mass;
		float m2 = mass;
		float a1 = upperPendulum.angle;
		float a2 = angle;
		float L1 = upperPendulum.armLength;
		float L2 = armLength;
		float w1 = upperPendulum.angularVelocity;
		float w2 = angularVelocity;

		/*
		using the numerical solution...aka the "Runge Kutta Method"
		w' = angular acceleration (in case u didnt know)

		w1' = 	−g (2 m1 + m2) sin a1 − m2 g sin(a1 − 2 * a2) − 2 sin(a1 − a2) m2 (w2^2 L2 + w1^2 L1 cos(a1 − a2))
				_______________________________________________________________________________________________

									L1(2 m1 + m2 − m2 cos(2 * a1 − 2 * a2))


		w2' = 	2 * sin(a1−a2) (w1^2 L1 (m1 + m2) + g(m1 + m2) cos a1 + w2^2 L2 m2 cos(a1 − a2))
				_____________________________________________________________________________

								L2 (2 * m1 + m2 − m2 cos(2 * a1 − 2 * a2))
		*/

		//first, find angular acceleration of the upper pendulum
		float num1 = -G * (2 * m1 + m2) * sin(a1);
		float num2 = -m2 * G * sin(a1 - 2 * a2);
		float num3 = -2 * sin(a1 - a2) * m2 * (w2 * w2 * L2 + w1 * w1 * L1 * cos(a1 - a2));
		float denominator = L1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		upperPendulum.angularAcceleration = (num1 + num2 + num3) / denominator;

		//now find the angular acceleration of the current pendulum
		num1 = 2 * sin(a1 - a2);
		num2 = w1 * w1 * L1 * (m1 + m2);
		num3 = G * (m1 + m2) * cos(a1) + w2 * w2 * L2 * m2 * cos(a1 - a2);
		denominator = L2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		angularAcceleration = (num1 * (num2 + num3)) / denominator;
}

//---------DRAW-----------
void PendulumSection::drawArm(sf::RenderWindow& window)
{
	window.draw(arm);
}
void PendulumSection::drawBody(sf::RenderWindow& window)
{
	window.draw(body);
}



