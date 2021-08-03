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
PendulumSection::PendulumSection(int mass, float angle, int armLength, PendulumSection* upperPendulum)
{
	joinPendulums(upperPendulum); //attach upper pendulum to this pendulum and this pendulum to upper pendulum
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
	arm = new sf::RectangleShape(sf::Vector2f(10, this->armLength)); //set width, length of arm
	arm->setOrigin(this->arm->getSize().x / 2, 0); //set orgin in middle at top of rectangle
	arm->setPosition(sf::Vector2f(this->startPosition.x, this->startPosition.y));
	arm->setFillColor(sf::Color(71, 71, 71));
	arm->setRotation(angle);
	arm->setOutlineColor(sf::Color(sf::Color::Black));
	arm->setOutlineThickness(4);

	//create the body visual
	body = new sf::CircleShape((mass/5.0f));
	body->setOrigin(sf::Vector2f(this->body->getRadius(), this->body->getRadius())); //set orgin as center of circle
	body->setPosition(getEndingPosition());
	body->setFillColor(sf::Color::White);
	body->setOutlineColor(sf::Color(sf::Color::Black));
	body->setOutlineThickness(3);
}
//destructor
PendulumSection::~PendulumSection()
{
	delete this->body;
	delete this->arm;
}

//-----------GETTERS------------
sf::Vector2f PendulumSection::getEndingPosition() //returns the end position of the pendulums arm
{
	sf::Vector2f endingPosition;
	endingPosition.x = startPosition.x - armLength * sin(angle);
	endingPosition.y = startPosition.y + armLength * cos(angle);
	return(endingPosition);
}

//-----------PENDULUM HELPERS-------
void PendulumSection::updatePos(float dt)
{
	angularVelocity += angularAcceleration * dt;
	angle += angularVelocity * dt;

	if (upperPendulum != nullptr)
	{
		startPosition = upperPendulum->getEndingPosition();
	}

	arm->setPosition(startPosition.x, startPosition.y);
	arm->setRotation(angle * (180 / PI));
	body->setPosition(this->getEndingPosition());
}
void PendulumSection::updatePendulum()
{
	if (upperPendulum == nullptr)
	{

	}
	else
	{
		//set the variables we need
		float m1 = upperPendulum->mass;
		float m2 = mass;
		float a1 = upperPendulum->angle;
		float a2 = angle;
		float L1 = upperPendulum->armLength;
		float L2 = armLength;
		float w1 = upperPendulum->angularVelocity;
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
		upperPendulum->angularAcceleration = (num1 + num2 + num3) / denominator;

		//now find the angular acceleration of the current pendulum
		num1 = 2 * sin(a1 - a2);
		num2 = w1 * w1 * L1 * (m1 + m2);
		num3 = G * (m1 + m2) * cos(a1) + w2 * w2 * L2 * m2 * cos(a1 - a2);
		denominator = L2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		angularAcceleration = (num1 * (num2 + num3)) / denominator;
	}
}
void PendulumSection::joinPendulums(PendulumSection* upperPendulum)
{
	this->upperPendulum = upperPendulum;
	upperPendulum->lowerPendulum = this;
}

//---------DRAW-----------
void PendulumSection::drawArm(sf::RenderWindow& window)
{
	window.draw(*arm);
}
void PendulumSection::drawBody(sf::RenderWindow& window)
{
	window.draw(*body);
}


