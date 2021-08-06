#include "Pendulum.h"

//constructor
Pendulum::Pendulum(int mass, float angle, int length, int x, int y)
{
	start(mass, angle, length, x, y);
}

int Pendulum::getSize()
{
    return pendulum.size();
}
sf::Color Pendulum::getArmColor()
{
    return armColor;
}

//start a new pendulum
void Pendulum::start(int mass, float angle, int length, int x, int y)
{
	PendulumSection currPendulum (mass, angle, length, x, y); //create the first arm+body for this new pendulum object
	pendulum.push_back(currPendulum); //add this first section to the pendulum variable
    newTrail(); //anytime start is called, we make a new body, therefore we need to add a trail.
}
//add to the existing pendulum
void Pendulum::add(int mass, float angle, int length)
{
	PendulumSection currPendulum(mass, angle, length, pendulum[pendulum.size()-1]);//mass, angle, arm length, upper pendulum
	pendulum.push_back(currPendulum); //add this next section to our pendulum variable
    newTrail(); //anytime add is called, we make a new body, therefore we need to add a trail.
}

//update pendulum's values
void Pendulum::calculatePendulum()
{
	for (int i = pendulum.size(); i > 1; i--) //start from bottom pendulum up, dont do top pendulum
	{
		pendulum[i-1].calculatePendulum(pendulum[i-2]);
	}
}
//update pendulums position
void Pendulum::updatePos(float simulationSpeed)
{

	pendulum[0].updatePos(simulationSpeed, pendulum[0], true); //update first section of pendulum  with "true" so function knows this is the first section
	for (int i = 1; i < pendulum.size(); i++)
	{
		pendulum[i].updatePos(simulationSpeed, pendulum[i-1], false); //update the rest of the sections
	}
}

//create a new trail
void Pendulum::newTrail()
{
   std::vector<sf::Vertex> singleTrail;
   trails.push_back(singleTrail);
}
//update trails
void Pendulum::updateTrails(std::string trailType)
{
    this->trailType = trailType;

    if (trailType == "Fade" || trailType == "Always") //if either of these, we create trails
    {
        while (trails.size() < pendulum.size()) //when trails is toggled off, all trails are cleared. When it is toggled back on, this makes sure each pendulum has a trail
        {
            newTrail();
        }

        float maxTrailSize = 350;
        sf::Vertex tempVertexHolder;

        for (int i = 0; i < pendulum.size(); i++)
        {
            tempVertexHolder.position = pendulum[i].getEndingPosition(); //set position of vertex to the end of this current pendulums arm

            //here, we set the vertex colors based on what style we are on. stle 1 we want custom colors, style 2 we want body colors, style 3 we want arm colors
            if (currStyle == "1")
            {
                if (i == 0)
                    tempVertexHolder.color = sf::Color(255, 194, 253);
                else if (i == 1)
                    tempVertexHolder.color = sf::Color(194, 252, 255);
                else 
                    tempVertexHolder.color = sf::Color(203, 245, 184);
            }
            else if (currStyle == "2")
                tempVertexHolder.color = pendulum[i].body.getFillColor();
            else
                tempVertexHolder.color = pendulum[i].arm.getFillColor();

            trails[i].push_back(tempVertexHolder); //push back the vertex to the trail we are on

            if (trailType == "Fade") //this allows the end of the trail to fade away so it is always a size of "maxTrailSize". For "always", we never wanna delete any part of the trail
            {
                if (trails[i].size() > maxTrailSize)
                    trails[i].erase(trails[i].begin(), trails[i].begin() + (trails[i].size() - (maxTrailSize - 25)));
            }

            float opacityCoefficient = 255.0f / trails[i].size(); //set opacity so trail in front is more solid, trail farther back is more see through
            for (int j = 0; j < trails[i].size(); j++)
            {
                trails[i][j].color.a = j * opacityCoefficient;
            }
        }
    }
    else //if trailType is "none", destory all trails
    {
        trails.clear();
    }
}
//update trail colors when "always" is on so if we switch colors or types, the trail colors all change
void Pendulum::updateTrailColors()
{
    //example: on style 1, always is on. Trails are currently style 1 colors. Switch to style 2. Now half of the trail is style 1 color and the other half is style 2
    //therefore, when switching styles and always is on, change all trail colors
    if (trailType == "Always")
    {
        for (int i = 0; i < trails.size(); i++)
            for (int j = 0; j < trails[i].size(); j++)
            {
                if (currStyle == "1")
                {
                    if (i == 0)
                        trails[i][j].color = sf::Color(255, 194, 253);
                    else if (i == 1)
                        trails[i][j].color = sf::Color(194, 252, 255);
                    else
                        trails[i][j].color = sf::Color(203, 245, 184);
                }
                else if (currStyle == "2")
                    trails[i][j].color = pendulum[i].body.getFillColor();
                else
                    trails[i][j].color = pendulum[i].arm.getFillColor();

                float opacityCoefficient = 255.0f / trails[i].size(); //set opacity so trail in front is solid, trail farther back is more see through
                trails[i][j].color.a = j * opacityCoefficient;
            }
    }
}

//help change to style 1
void Pendulum::styleOne()
{
    currStyle = "1";
    for (int i = 0; i < pendulum.size(); i++)
    {
        //set arms back to their normal color
        pendulum[i].arm.setFillColor(sf::Color(156, 156, 156));
        pendulum[i].arm.setOutlineColor(sf::Color::Black);

        pendulum[i].setArmLength(400); //set arm length to normal
        pendulum[i].setMass(133.33); //set mass back to noraml

        pendulum[i].arm.setSize(sf::Vector2f(10, pendulum[i].getArmLength())); //update arm size to set the width and length back to the normal;

        //set bodies back to their normal color
        pendulum[i].body.setFillColor(sf::Color(219, 219, 219));
        pendulum[i].body.setOutlineColor(sf::Color::Black);
    }
    updateTrailColors(); //this only does something when the trailtype is "Always"
}
//help change to style 2
void Pendulum::styleTwo()
{
    currStyle = "2";
    //first set all arms to transparent
    for (int i = 0; i < pendulum.size(); i++)
    {
        pendulum[i].arm.setOutlineColor(sf::Color::Transparent);
        pendulum[i].arm.setFillColor(sf::Color::Transparent);

        pendulum[i].setArmLength(400); //set arm length back to noraml
        pendulum[i].setMass(133.33); //set mass back to noraml

        pendulum[i].arm.setSize(sf::Vector2f(10, pendulum[i].getArmLength())); //update arm size to set the width and length back to the normal;
    }

    //now set the first body to transparent so we cant see it, and the rest to a random color
    pendulum[0].body.setFillColor(sf::Color::Transparent);
    pendulum[0].body.setOutlineColor(sf::Color::Transparent);
    for (int i = 1; i < pendulum.size(); i++) //start at one to skip first body
    {
        pendulum[i].body.setFillColor(getRandomColor());
        pendulum[i].body.setOutlineColor(sf::Color::Black);
    }
    updateTrailColors();//this only does something when the trailtype is "Always"
}
//help change to style 3
void Pendulum::styleThree(sf::Color newArmColor)
{
    currStyle = "3";
    armColor = newArmColor;

    for (int i = 0; i < pendulum.size(); i++)
    {
        pendulum[i].body.setFillColor(sf::Color::Transparent);
        pendulum[i].body.setOutlineColor(sf::Color::Transparent);
        pendulum[i].arm.setFillColor(armColor);
        pendulum[i].arm.setOutlineColor(armColor);

        pendulum[i].setArmLength(441); //set arm length a little longer
        pendulum[i].setMass(147); //keep mass even with arm length (1/3 of it)

        pendulum[i].arm.setSize(sf::Vector2f(1, pendulum[i].getArmLength()));
    }
    updateTrailColors();//this only does something when the trailtype is "Always"
}

//draw the arms
void Pendulum::drawArm(sf::RenderWindow& window)
{
	for (int i = 0; i < pendulum.size(); i++)
		pendulum[i].drawArm(window);
}
//draw the bodies
void Pendulum::drawBody(sf::RenderWindow& window)
{
	for (int i = 0; i < pendulum.size(); i++) //draw lower bodies first so they show up in front of the upper bodies
		pendulum[i].drawBody(window);
}
//draw pendulums trails
void Pendulum::drawTrail(sf::RenderWindow& window)
{
    
    if (trailType == "Always" || trailType == "Fade")
    {
        for (int i = 0; i < trails.size(); i++)
        {
            if (trails[i].size() > 0)
            {
                window.draw(&trails[i][0], trails[i].size(), sf::LineStrip);
            }

        }
    }
    
}

//get a nice looking bright and random color
sf::Color Pendulum::getRandomColor()
{
    float H = rand() % 335 + 1;
    float S = 50;
    float V = 100;
    return HSVtoRGB(H, S, V);
}
//converts hsv colors to rgb colors
sf::Color Pendulum::HSVtoRGB(float H, float S, float V)
{
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }
    float R = (r + m) * 255;
    float G = (g + m) * 255;
    float B = (b + m) * 255;

    return sf::Color(R, G, B);
}
