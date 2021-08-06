#ifndef SIMULATION_H
#define SIMULATION_H

#define PI 3.14159265
#define LOG(x) std::cout << x << std::endl
#include <iostream>
#include <string>
#include <vector>
#include "PendulumSection.h"
#include "Pendulum.h"

class Simulation
{
private:

    sf::ContextSettings settings; //settings so we can add anti aliasing
    sf::RenderWindow window; //the window we will run simulation in
    sf::Clock clock; //clock so we can have time variables. Allows us to keep the same speed when framerate is changed
    sf::Clock trailClock;

    sf::CircleShape pendulumHolder; //this will be the circle shape to appear to "hold" the pendulums. Purely for aesthetical reasons
    sf::Font font; //font we will use
    sf::Text simSpeedText; //text we will use to display simulation speed
    sf::Text currStyleText; //text we will use to display current style
    sf::Text controlsText; //text we will use to display the controls
    sf::Text trailTypeText; //text we will use to display the current trail type
    sf::Color bgColor; //color for background

    std::vector<Pendulum> pendulums; //vector of all the pendulums

    float currSimulationSpeed = 1; //tracks the current simulation speed we want to run at
    bool isPaused = false; //tracks if game is currently paused or not
    bool isControlsShowing = false; //tracks if we currently want to show the controls or not
    int style3TransparencyHelp = 1; //helps us change transparencies every time style 3 is called

    std::string trailType = "Fade"; //tracks the current trail type. Types are "fade", "none", "always"
    std::string currStyle = "1"; //tracks the current style the simulation is running in

public:
    Simulation(); //constructor
    void initialize(); //initialize variables
    void runSimulation(); //function to run the program
    void checkForInput(); //check for user input

    //-------ADDING OBJECTS----------
    void addSinglePendulum(float firstDesiredAngle, float secondDesiredInc); //add a new double pendulum, with angle 1 for section 1 and angle 2 for section 2
    void addSingleSection(float desiredAngle); //add another section (arm+body) to current pendulum we are on with desired angle
    void addMultiplePendulums(float totalAngleDifference, float numPendulums); //spawn multiple double pendulums at once with a total angle difference in radians between first pendulum spawned and last pendulum spawned.  Helps with style 3 for the butterfly effect
    void addMultipleSections(float totalAngleDifference); //spawn another section for every existing pendulum with a total angle difference in radians between first secion spawned and last section spawned. Helps with style 3 for the butterfly effect

    //----------STYLE FUNCTIONS-----------
    void styleOne(); //lets us change to style 1. normal style
    void styleTwo(); //lets us change to style 2. hide arms and first bodies. make all other bodies bright colors
    void styleThree(); //lets us change to style 3. allows us to see the butterfy effect
    int styleThreeTransparencyHelp();     //help for changing style 3 transparency
    void styleThreeColorHelpOne(); //help selecting colors with method 1 and applying for style 3 
    void styleThreeColorHelpTwo(); //help selecting colors with method 2 and applying for style 3 

    //---------MISC CONTROLS----------
    void clear(); //clear screen when called
    void changeSimulationSpeed(float upOrDown); //helps change the simulation speed
    void changeTrailType(); //helps us toggle trails on and off
    void togglePause(); //helps pause and unpause game
    void toggleControls(); //helps show and hide controls

    //--------DRAW UPDATE FUNCTIONS---------------------
    void updatePendulums(); //update the pendulums
    void updateText(); //update text objects
    void drawObjects(); //draw objects (lines, balls, trails)

    //---------COLOR FUNCTIONS----------
    sf::Color getRandomColor(); //get random nice looking and bright color
    sf::Color HSVtoRGB(float H, float S, float V); //convert hsv values to rgb values

};

#endif //SIMULATION_H